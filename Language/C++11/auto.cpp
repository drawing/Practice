/**
 * g++ -std=c++0x auto.cpp
 */

#include <vector>
#include <iostream>

using namespace std;

auto func() -> int {
	int a = 10;
	return a;
}

int main()
{
	vector<int> vec;
	vec.push_back(1);

	auto i = vec.begin();	// vector<int>::iterator
	auto j = 0;		// int

	cout << *i << endl;
	cout << vec[j] << endl;

	int b = func();
	return 0;
}

