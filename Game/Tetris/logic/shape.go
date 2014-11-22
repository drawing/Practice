package logic

import (
	"math/rand"
)

type Square [VA_SHAPE_SIZE][VA_SHAPE_SIZE]int

type Position struct {
	Row int
	Col int
}

type Shape struct {
	square []Square
	index  int
}

func (s *Shape) Rotate() *Square {
	s.index = (s.index + 1) % len(s.square)
	return &s.square[s.index]
}

func (s *Shape) NextRotate() *Square {
	return &s.square[(s.index+1)%len(s.square)]
}

func (s *Shape) Current() *Square {
	return &s.square[s.index]
}

func RandomOneShape() *Shape {
	sel := rand.Int() % len(AllShape)
	shape := &Shape{AllShape[sel], 0}
	shape.index = rand.Int() % len(shape.square)
	return shape
}

var AllShape = [][]Square{
	Shape_S,
	Shape_Z,
	Shape_L,
	Shape_J,
	Shape_O,
	Shape_T,
	Shape_L,
	Shape_I,
}

var Shape_S = []Square{
	{
		{0, 10, 10, 0},
		{10, 10, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
	},
	{
		{10, 0, 0, 0},
		{10, 10, 0, 0},
		{0, 10, 0, 0},
		{0, 0, 0, 0},
	},
}

var Shape_Z = []Square{
	{
		{11, 11, 0, 0},
		{0, 11, 11, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
	},
	{
		{0, 11, 0, 0},
		{11, 11, 0, 0},
		{11, 0, 0, 0},
		{0, 0, 0, 0},
	},
}

var Shape_L = []Square{
	{
		{12, 0, 0, 0},
		{12, 0, 0, 0},
		{12, 12, 0, 0},
		{0, 0, 0, 0},
	},
	{
		{0, 0, 12, 0},
		{12, 12, 12, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
	},
	{
		{12, 12, 0, 0},
		{0, 12, 0, 0},
		{0, 12, 0, 0},
		{0, 0, 0, 0},
	},
	{
		{12, 12, 12, 0},
		{12, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
	},
}

var Shape_J = []Square{
	{
		{0, 13, 0, 0},
		{0, 13, 0, 0},
		{13, 13, 0, 0},
		{0, 0, 0, 0},
	},
	{
		{13, 0, 0, 0},
		{13, 13, 13, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
	},
	{
		{13, 13, 0, 0},
		{13, 0, 0, 0},
		{13, 0, 0, 0},
		{0, 0, 0, 0},
	},
	{
		{13, 13, 13, 0},
		{0, 0, 13, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
	},
}

var Shape_O = []Square{
	{
		{14, 14, 0, 0},
		{14, 14, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
	},
}

var Shape_T = []Square{
	{
		{0, 15, 0, 0},
		{15, 15, 15, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
	},
	{
		{0, 15, 0, 0},
		{0, 15, 15, 0},
		{0, 15, 0, 0},
		{0, 0, 0, 0},
	},
	{
		{0, 0, 0, 0},
		{15, 15, 15, 0},
		{0, 15, 0, 0},
		{0, 0, 0, 0},
	},
	{
		{0, 15, 0, 0},
		{15, 15, 0, 0},
		{0, 15, 0, 0},
		{0, 0, 0, 0},
	},
}

var Shape_I = []Square{
	{
		{0, 16, 0, 0},
		{0, 16, 0, 0},
		{0, 16, 0, 0},
		{0, 16, 0, 0},
	},
	{
		{0, 0, 0, 0},
		{16, 16, 16, 16},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
	},
}
