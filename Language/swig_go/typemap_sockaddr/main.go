package main

import (
	"./address"
	"fmt"
)

func main() {
	k := address.GetAddress()
	fmt.Println(k)

	g := address.NewSockAddr()
	g.Assign("192.168.1.9:7890")
	fmt.Println(g)
}
