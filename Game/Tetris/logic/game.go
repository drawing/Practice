package logic

import (
	"fmt"
)

type Game struct {
	plat  Plat
	score int
	shape *Shape
	pos   Position
}

type Direction struct {
	RowShift int
	ColShift int
}

var DI_UP = Direction{-1, 0}
var DI_DOWN = Direction{1, 0}
var DI_LEFT = Direction{0, -1}
var DI_RIGHT = Direction{0, 1}

func (g *Game) Init() {
	g.shape = RandomOneShape()
	g.pos.Col = (VA_PLAT_WIDTH + VA_WALL_DEPTH) / 2
	g.pos.Row = VA_WALL_DEPTH
	g.plat.Init()
}

func (g *Game) Check(plat *Plat, pos *Position, shape *Square) bool {
	for i := 0; i < VA_SHAPE_SIZE; i++ {
		for j := 0; j < VA_SHAPE_SIZE; j++ {
			if shape[i][j] != 0 &&
				plat.cell[pos.Row+i][pos.Col+j] != 0 {
				return false
			}
		}
	}
	return true
}

func (g *Game) Freeze(plat *Plat, pos *Position, shape *Square) bool {
	// 1. freeze the shape to Plat
	for i := 0; i < VA_SHAPE_SIZE; i++ {
		for j := 0; j < VA_SHAPE_SIZE; j++ {
			if shape[i][j] != 0 {
				plat.cell[pos.Row+i][pos.Col+j] = shape[i][j]
			}
		}
	}

	// 2. eliminate the full line
	elimLine := 0
	for i := 0; i < VA_SHAPE_SIZE; i++ {
		elim := plat.Eliminate(i + pos.Row)
		if elim {
			elimLine++
		}
	}
	g.score += elimLine

	// 3. random one new shape
	g.shape = RandomOneShape()
	g.pos.Col = (VA_PLAT_WIDTH + VA_WALL_DEPTH) / 2
	g.pos.Row = VA_WALL_DEPTH

	return true
}

func (g *Game) Move(direction Direction) {
	if g.Check(&g.plat, &Position{g.pos.Row + direction.RowShift, g.pos.Col + direction.ColShift},
		g.shape.Current()) {
		g.pos.Row += direction.RowShift
		g.pos.Col += direction.ColShift
		return
	}

	if direction == DI_DOWN {
		g.Freeze(&g.plat, &g.pos, g.shape.Current())
	}
}

func (g *Game) Rotate() {
	s := g.shape.NextRotate()
	if g.Check(&g.plat, &g.pos, s) {
		g.shape.Rotate()
	}
}

func (g *Game) Show() {
	fmt.Println("Score: ", g.score)
	for i := 0; i < len(g.plat.cell); i++ {
		for j := 0; j < len(g.plat.cell[i]); j++ {
			if i >= g.pos.Row && i < g.pos.Row+4 &&
				j >= g.pos.Col && j < g.pos.Col+4 &&
				g.shape.Current()[i-g.pos.Row][j-g.pos.Col] != 0 {
				fmt.Printf("%2d ", g.shape.Current()[i-g.pos.Row][j-g.pos.Col])

			} else {
				fmt.Printf("%2d ", g.plat.cell[i][j])
			}

		}
		fmt.Println("")
	}
}
