package main

import (
	"./logic"

	"bufio"
	"github.com/nsf/termbox-go"
	"os"
	"time"
)

func draw(game *logic.Game) {
	// w, h := termbox.Size()
	termbox.Clear(termbox.ColorDefault, termbox.ColorDefault)

	plat := game.GetPlat()

	for i := 0; i < len(plat); i++ {
		for j := 0; j < len(plat[i])*2; j += 2 {
			cl := plat[i][j/2]%8 + 1
			if cl == 1 && plat[i][j/2] != 0 {
				cl = 3
			}
			termbox.SetCell(j, i, ' ', termbox.ColorDefault,
				termbox.Attribute(cl))
			termbox.SetCell(j+1, i, ' ', termbox.ColorDefault,
				termbox.Attribute(cl))
		}
	}
	termbox.Flush()
}

func main() {
	var game logic.Game
	game.Init()

	err := termbox.Init()
	if err != nil {
		panic(err)
	}
	defer termbox.Close()

	event_queue := make(chan termbox.Event)
	go func() {
		for {
			event_queue <- termbox.PollEvent()
		}
	}()

	time_line := make(chan int)
	go func() {
		for {
			time.Sleep(500 * time.Millisecond)
			time_line <- 1
		}
	}()

	for {
		draw(&game)
		select {
		case ev := <-event_queue:
			if ev.Type == termbox.EventKey {
				switch ev.Key {
				case termbox.KeyEsc:
					return
				case termbox.KeyArrowDown:
					game.Move(logic.DI_DOWN)
				case termbox.KeyArrowLeft:
					game.Move(logic.DI_LEFT)
				case termbox.KeyArrowRight:
					game.Move(logic.DI_RIGHT)
				case termbox.KeyArrowUp:
					game.Rotate()
				}
			}
		case <-time_line:
			game.Move(logic.DI_DOWN)
		}
	}

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
