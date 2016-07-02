package main

import (
	"log"
	"time"

	"github.com/coreos/etcd/raft"
	"github.com/coreos/etcd/raft/raftpb"
	"golang.org/x/net/context"
)

type SimpleNode struct {
	Id   uint64
	Recv chan raftpb.Message
	Send chan raftpb.Message

	Node    raft.Node
	storage *raft.MemoryStorage
}

const (
	NODE_COUNT = 3
)

func doRaftLogic(node *SimpleNode, nodes map[uint64]*SimpleNode) {
	ticker := time.Tick(100 * time.Millisecond)

	for {
		select {
		case <-ticker:
			node.Node.Tick()
		case rd := <-node.Node.Ready():
			// log.Println("recv msg:", rd)
			node.storage.Append(rd.Entries)
			time.Sleep(time.Millisecond)

			for _, entry := range rd.Entries {
				if entry.Type == raftpb.EntryNormal {
					log.Println(node.Id, "entry data:", string(entry.Data))
				}
			}

			for _, m := range rd.Messages {
				nodes[m.To].Recv <- m
			}
			node.Node.Advance()
		case msg := <-node.Recv:
			node.Node.Step(context.TODO(), msg)
		}
	}
}

func main() {
	nodes := map[uint64]*SimpleNode{}
	peers := []raft.Peer{}

	// 1. construct peers
	for i := uint64(1); i < NODE_COUNT+1; i++ {
		peer := raft.Peer{i, nil}
		peers = append(peers, peer)
	}

	// 2. construct Nodes
	for i := uint64(1); i < NODE_COUNT+1; i++ {
		storage := raft.NewMemoryStorage()
		conf := &raft.Config{
			ID:              i,
			ElectionTick:    10,
			HeartbeatTick:   1,
			Storage:         storage,
			MaxSizePerMsg:   4096,
			MaxInflightMsgs: 256,
		}
		log.Println("new node:", conf)
		node := raft.StartNode(conf, peers)

		simpleNode := &SimpleNode{
			Id:      i,
			Recv:    make(chan raftpb.Message, 255),
			Send:    make(chan raftpb.Message, 255),
			Node:    node,
			storage: storage,
		}
		nodes[i] = simpleNode
	}

	// 3. start node
	for _, node := range nodes {
		go doRaftLogic(node, nodes)
	}

	log.Println("Start Sleep")
	time.Sleep(500 * time.Millisecond)
	log.Println("Start Propose")

	nodes[1].Node.Propose(context.TODO(), []byte("Data1"))
	nodes[2].Node.Propose(context.TODO(), []byte("Data2"))

	time.Sleep(10 * time.Second)
}
