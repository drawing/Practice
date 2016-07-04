package main

import (
	"bytes"
	"encoding/gob"
	"encoding/json"
	"flag"
	"fmt"
	"io/ioutil"
	"log"
	"sync"
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

type Config struct {
	ID       uint64
	PeerAddr string
	ReqAddr  string
}

type KVEncode struct {
	Key   string
	Value string
}

type MemKV struct {
	mutex sync.Mutex
	kv    map[string]string
}

func (kv *MemKV) Set(key, value string) {
	if kv != nil {
		kv.mutex.Lock()
		defer kv.mutex.Unlock()
		kv.kv[key] = value

		fmt.Println("-----ALL KEY-VALUE BEGIN-----")
		for k, v := range kv.kv {
			fmt.Printf("\tkey=%s\tvalue=%s\n", k, v)
		}
		fmt.Println("-----ALL KEY-VALUE END-----")
	}
}

func (kv *MemKV) Get(key string) (string, bool) {
	if kv != nil {
		kv.mutex.Lock()
		defer kv.mutex.Unlock()
		value, present := kv.kv[key]
		return value, present
	}
	return "", false
}

var memkv *MemKV = &MemKV{
	kv: map[string]string{},
}

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
				} else if entry.Type == raftpb.EntryNormal {
					data := bytes.NewBuffer(entry.Data)
					var kv KVEncode
					err := gob.NewDecoder(data).Decode(&kv)
					if err != nil {
						log.Println("decode commit data failed:", err)
					} else {
						memkv.Set(kv.Key, kv.Value)
					}
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

func StartSimpleNode(self Config, config []Config) *SimpleNode {
	log.Println("start:", self.ID, config)

	raftPeers := []raft.Peer{}

	// 1. construct peers
	for _, conf := range config {
		peer := raft.Peer{conf.ID, nil}
		raftPeers = append(raftPeers, peer)
	}
	log.Println("peers", raftPeers)

	storage := raft.NewMemoryStorage()
	conf := &raft.Config{
		ID:              self.ID,
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
		ID: types.ID(self.ID),
		URLs: []neturl.URL{
			neturl.URL{
				Scheme: "http",
				Host:   self.PeerAddr,
			},
		},
		Raft:        simple,
		ClusterID:   types.ID(0x100),
		LeaderStats: stats.NewLeaderStats(types.ID(self.ID).String()),
		ServerStats: serverStats,
	}

	simple.transport = transport

	go simple.doRaftLogic()
	go http.ListenAndServe(self.PeerAddr, transport.Handler())

	transport.Start()
	for _, conf := range config {
		if conf.ID == self.ID {
			continue
		}
		// transport.AddRemote(types.ID(conf.ID), []string{"http://" + conf.PeerAddr})
		transport.AddPeer(types.ID(conf.ID), []string{"http://" + conf.PeerAddr})
	}

	return simple
}

func main() {
	var id uint64
	flag.Uint64Var(&id, "id", 1, "node id")
	flag.Parse()

	config := []Config{}
	confdata, err := ioutil.ReadFile("./json.conf")
	if err != nil {
		log.Fatalln("read config failed:", err)
	}

	err = json.Unmarshal(confdata, &config)
	if err != nil {
		log.Fatalln("Unmarshal config failed:", err)
	}

	var self Config
	// 1. construct peers
	for _, conf := range config {
		if id == conf.ID {
			self = conf
			break
		}
	}
	if self.ID == 0 {
		log.Fatalln("node id not found")
	}

	node := StartSimpleNode(self, config)

	http.HandleFunc("/add", func(w http.ResponseWriter, r *http.Request) {
		log.Println("add:", r.PostFormValue("KEY"), r.PostFormValue("VALUE"))

		kv := KVEncode{r.PostFormValue("KEY"), r.PostFormValue("VALUE")}
		if kv.Key == "" || kv.Value == "" {
			w.WriteHeader(400)
			return
		}
		var data bytes.Buffer
		err := gob.NewEncoder(&data).Encode(kv)
		if err != nil {
			w.WriteHeader(500)
			return
		}
		err = node.node.Propose(context.TODO(), data.Bytes())
		if err == nil {
			w.WriteHeader(200)
			w.Write([]byte("OK"))
		} else {
			w.WriteHeader(500)
			w.Write([]byte(err.Error()))
		}

	})

	http.HandleFunc("/get", func(w http.ResponseWriter, r *http.Request) {
		log.Println("get:", r.PostFormValue("KEY"))
		key := r.PostFormValue("KEY")
		if key == "" {
			w.WriteHeader(400)
			return
		}
		value, present := memkv.Get(key)
		if present {
			fmt.Fprintf(w, "KEY=%s, VALUE=%s", key, value)
		} else {
			fmt.Fprintln(w, "key not found:", key)
		}
	})

	log.Fatal(http.ListenAndServe(self.ReqAddr, nil))
}
