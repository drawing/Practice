
# etcd raft 使用示例

按照顺序，每一个示例都是在上一个示例基础上修改而成

## simple

"etcd/raft" 的最简单的示例代码，使用管道的方式模拟多个节点通讯，完成raft节点的基本运行。

## network

在 simple 基础上，将管道更换成 "etcd/rafthttp"，通过网络通讯完成 raft 节点交互

## memkv

raft实现全内存的kv系统，无快照，不能增删节点，仅保持各个节点数据一致性。
使用：
```
./memkv --id=1
./memkv --id=2
./memkv --id=3
```
分别启动三个节点，可增删key-value数据。

增加kv值命令：
```
curl -d "KEY=k1&VALUE=v1" "http://127.0.0.1:9101/add"
```

## memkv2

增加动态增删节点能力：在 memkv 基础上使用最简单的方式，每隔几秒记载`json.conf`文件中的配置作为集群节点，可通过运行时手工修改配置增删节点。


## wal

memkv2的基础上，以wal方式持久化存储数据（由于没有快照，在数据量比较大的情况下启动较慢），使用etcd的wal实现。


## snapshot

TODO: 增加快照方式
