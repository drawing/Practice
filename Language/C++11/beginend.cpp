#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
	int a[] = {2, 1, 3};
	std::sort(std::begin(a), std::end(a));
	for (auto v : a) {
		cout << v << " ";
	}
	cout << endl;
	return 0;
}

