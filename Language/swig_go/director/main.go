package main

import "./dir"
import "fmt"

var thread dir.GoThread

type Callback struct {
}

func (cb *Callback) Do(data string) {
	fmt.Println(data)
}

func SetCallback() {
	cb := dir.NewDirectorICallback(&Callback{})
	thread.SetCallback(cb)
}

func main() {
	thread = dir.NewGoThread()

	SetCallback()
	thread.RunLoop()
}
