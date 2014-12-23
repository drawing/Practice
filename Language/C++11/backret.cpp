
class Map {
public:
	struct Cell {
		int color;
	};

	Cell * GetCell(int x, int y);
	Cell * ClearCell(int x, int y);
};

Map::Cell * Map::GetCell(int, int)
{
	return nullptr;
}

auto Map::ClearCell(int, int) -> Cell*
{
	return nullptr;
}

int main() {
	return 0;
}
