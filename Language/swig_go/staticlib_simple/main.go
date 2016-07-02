package main

import "./network"
import "fmt"

func main() {
	var addr network.Address = network.NewAddress()
	fmt.Println(addr.Network())
	fmt.Println(addr.String())
	network.DeleteAddress(addr)
}
