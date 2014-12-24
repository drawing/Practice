#include <iostream>

using namespace std;

constexpr int add(const int a, const int b)
{
	return a + b;
}

int main()
{
	const int c1 = 100;
	int c2 = 200;

	const int c3 = c2 * 2;
	// complie error
	// constexpr int c4 = c2 * 2;
	constexpr int c5 = c1 * 2;
	constexpr int c6 = add(10, 20);

	constexpr int c7 = add(c6, c5);
	// complie error
	// constexpr int c8 = add(c2, c2);

	cout << add(10, 20) << endl;
	int a, b;
	cin >> a >> b;
	cout << add(a, b) << endl;
	return 0;
}
