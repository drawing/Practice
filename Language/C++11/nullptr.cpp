#include <iostream>

using namespace std;

int main()
{
	int * p = NULL;
	int * q = nullptr;

	// true
	cout << (p == q) << endl;

	// complie failed
	// int i = nullptr;
	return 0;
}

