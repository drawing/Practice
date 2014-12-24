#include <iostream>

using namespace std;

std::tuple<int, int, int, int> fun() {
	return std::make_tuple(1, 2, 3, 4);
}

int main()
{
	int a, b, c, d;
	std::tie(a, b, c, d) = fun();
	cout << a << " " << b << " " << c << endl;
	return 0;
}

