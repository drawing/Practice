package main

import (
	"log"
	"time"

	"net/http"
	neturl "net/url"

	"github.com/coreos/etcd/etcdserver/stats"
	"github.com/coreos/etcd/pkg/types"
	"github.com/coreos/etcd/raft"
	"github.com/coreos/etcd/raft/raftpb"
	"github.com/coreos/etcd/rafthttp"
	"golang.org/x/net/context"
)

type SimpleNode struct {
	node      raft.Node
	storage   *raft.MemoryStorage
	transport *rafthttp.Transport
}

func (n *SimpleNode) Process(ctx context.Context, m raftpb.Message) error {
	// log.Println("process:", m)
	n.node.Step(ctx, m)
	return nil
}

func (n *SimpleNode) IsIDRemoved(id uint64) bool {
	log.Println("IsIDRemoved:", id)
	return false
}

func (n *SimpleNode) ReportUnreachable(id uint64) {
	log.Println("ReportUnreachable:", id)
}

func (n *SimpleNode) ReportSnapshot(id uint64, status raft.SnapshotStatus) {
	log.Println("ReportSnapshot:", id, status)
}

func (n *SimpleNode) doRaftLogic() {
	ticker := time.Tick(100 * time.Millisecond)

	for {
		select {
		case <-ticker:
			n.node.Tick()
		case rd := <-n.node.Ready():
			// log.Println("msg:", rd)
			// 1. HardState
			if !raft.IsEmptyHardState(rd.HardState) {
				n.storage.SetHardState(rd.HardState)
			}
			// 2. Entries
			n.storage.Append(rd.Entries)
			// 3. Snapshot
			if !raft.IsEmptySnap(rd.Snapshot) {
				n.storage.ApplySnapshot(rd.Snapshot)
			}

			for _, entry := range rd.CommittedEntries {
				log.Println("commit:", entry)
				if entry.Type == raftpb.EntryConfChange {
					var cc raftpb.ConfChange
					cc.Unmarshal(entry.Data)
					n.node.ApplyConfChange(cc)
				}
			}

			// log.Println("send msg:", rd.Messages)
			n.transport.Send(rd.Messages)
			n.node.Advance()
		}
	}
}

type Peer struct {
	id  uint64
	url string
}

func StartSimpleNode(id uint64, url string, peers []Peer) *SimpleNode {
	log.Println("start:", id, url)

	raftPeers := []raft.Peer{}

	// 1. construct peers
	for _, p := range peers {
		peer := raft.Peer{p.id, nil}
		raftPeers = append(raftPeers, peer)
	}
	raftPeers = append(raftPeers, raft.Peer{id, nil})
	log.Println("peers", raftPeers)

	storage := raft.NewMemoryStorage()
	conf := &raft.Config{
		ID:              id,
		ElectionTick:    10,
		HeartbeatTick:   1,
		Storage:         storage,
		MaxSizePerMsg:   4096,
		MaxInflightMsgs: 256,
	}

	node := raft.StartNode(conf, raftPeers)

	simple := &SimpleNode{
		node:    node,
		storage: storage,
	}

	serverStats := &stats.ServerStats{}
	serverStats.Initialize()
	transport := &rafthttp.Transport{
		ID: types.ID(id),
		URLs: []neturl.URL{
			neturl.URL{
				Host: url,
			},
		},
		Raft:        simple,
		ClusterID:   types.ID(0x100),
		LeaderStats: stats.NewLeaderStats(types.ID(id).String()),
		ServerStats: serverStats,
	}

	simple.transport = transport

	go simple.doRaftLogic()
	go http.ListenAndServe(url, transport.Handler())

	transport.Start()
	for _, p := range peers {
		transport.AddRemote(types.ID(p.id), []string{"http://" + p.url})
		transport.AddPeer(types.ID(p.id), []string{"http://" + p.url})
	}

	return simple
}

func main() {
	p1 := Peer{0x1, "127.0.0.1:9001"}
	p2 := Peer{0x2, "127.0.0.1:9002"}
	p3 := Peer{0x3, "127.0.0.1:9003"}

	s1 := StartSimpleNode(p1.id, p1.url, []Peer{p2, p3})
	s2 := StartSimpleNode(p2.id, p2.url, []Peer{p1, p3})
	StartSimpleNode(p3.id, p3.url, []Peer{p1, p2})

	time.Sleep(3 * time.Second)

	log.Println("propose start")
	s1.node.Propose(context.TODO(), []byte("data1"))
	s2.node.Propose(context.TODO(), []byte("data2"))
	log.Println("propose end")

	time.Sleep(100 * time.Second)
}
