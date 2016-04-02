package main

import "fmt"
import "./vector"

func main() {
	v := vector.NewVectori()
	v.Add(12)
	v.Add(213)
	vector.PrintList(v)
	fmt.Println("finish")
}
