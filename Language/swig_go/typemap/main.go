package main

import (
	"./address"
	"fmt"
)

func main() {
	var k string = address.GetAddress()
	fmt.Println(k)
}
