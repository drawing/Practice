package main

import (
	"./logic"

	"bufio"
	"os"
)

func main() {
	var game logic.Game
	game.Init()
	game.Show()

	reader := bufio.NewReader(os.Stdin)
	for {
		data, _ := reader.ReadByte()
		command := data
		switch command {
		case 'q':
			os.Exit(0)
		case 's':
			game.Move(logic.DI_DOWN)
		case 'a':
			game.Move(logic.DI_LEFT)
		case 'd':
			game.Move(logic.DI_RIGHT)
		case 'w':
			game.Move(logic.DI_UP)
		case 'r':
			game.Rotate()
		}
		game.Show()
	}
}
