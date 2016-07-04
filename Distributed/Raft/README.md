
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
./memkv --id=1
./memkv --id=1
```
分别启动三个节点，可增删key-value数据。

## memkv2

在 memkv 基础上增加配置持久化以及动态增删节点能力
