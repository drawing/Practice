#include <iostream>

using namespace std;

std::tuple<int, int, int> fun() {
	return std::make_tuple(1, 2, 3);
}

int main()
{
	int a, b, c;
	std::tie(a, b, c) = fun();
	cout << a << " " << b << " " << c << endl;
	return 0;
}

