package main

import (
	_ "./build/"

	"golang.org/x/mobile/app"
	_ "golang.org/x/mobile/bind/java"
)

func main() {
	app.Run(app.Callbacks{})
}
