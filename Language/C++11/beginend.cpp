#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
	int a[] = {2, 1, 3};
	std::sort(std::begin(a), std::end(a));
	for (int i = 0; i < sizeof(a)/sizeof(a[0]); i++) {
		cout << a[i] << " ";
	}
	cout << endl;
	return 0;
}

