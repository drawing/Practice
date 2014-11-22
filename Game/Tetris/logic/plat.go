package logic

/*
plat example:

       c1 c2 c3 c4 c5 c6 c7
    -----------------------
h0  |  1  1  1  1  1  1  1
h1  |  1  1  1  1  1  1  1
h2  |  1  1  0  0  0  1  1
h3  |  1  1  0  0  0  1  1
h4  |  1  1  0  0  0  1  1
h5  |  1  1  1  1  1  1  1
h6  |  1  1  1  1  1  1  1
*/

type Plat struct {
	cell [VA_WORLD_HEIGHT][VA_WORLD_WIDTH]int
}

func (p *Plat) Init() {
	for i := 0; i < VA_WORLD_WIDTH; i++ {
		for j := 0; j < VA_WALL_DEPTH; j++ {
			p.cell[j][i] = 1
			p.cell[VA_WORLD_HEIGHT-1-j][i] = 1
		}
	}
	for j := 0; j < VA_WORLD_HEIGHT; j++ {
		for i := 0; i < VA_WALL_DEPTH; i++ {
			p.cell[j][i] = 1
			p.cell[j][VA_WORLD_WIDTH-1-i] = 1
		}
	}
}

func (p *Plat) Eliminate(height int) bool {
	if height-VA_WALL_DEPTH < 0 ||
		height-VA_WALL_DEPTH >= VA_PLAT_HEIGHT {
		return false
	}

	// check
	for i := VA_WALL_DEPTH; i < VA_PLAT_WIDTH+VA_WALL_DEPTH; i++ {
		if p.cell[height][i] == 0 {
			return false
		}
	}

	// down
	for i := height; i >= VA_WALL_DEPTH; i-- {
		for j := VA_WALL_DEPTH; j <= VA_PLAT_WIDTH+VA_WALL_DEPTH; j++ {
			if i == VA_WALL_DEPTH {
				p.cell[i][j] = 0
			} else {
				p.cell[i][j] = p.cell[i-1][j]
			}
		}
	}

	return true
}
