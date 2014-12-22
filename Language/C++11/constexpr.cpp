#include <iostream>

using namespace std;

constexpr int add(int a, int b)
{
	return a + b;
}

int main()
{
	cout << add(10, 20) << endl;
	int a, b;
	cin >> a >> b;
	cout << add(a, b) << endl;
	return 0;
}
