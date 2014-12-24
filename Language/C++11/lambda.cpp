#include <iostream>
#include <vector>

using namespace std;

int main()
{
	vector<int> vec;
	vec.push_back(9);
	vec.push_back(1);
	vec.push_back(1);

	int out = 0;
	
	// can not access out var
	std::for_each(vec.begin(), vec.end(), [](int v){ cout << v << endl;});
	cout << endl;

	// can access out but cannot modify it
	std::for_each(vec.begin(), vec.end(), [=](int v){ cout << v << ":" << out << endl;});
	cout << endl;

	// can modify it
	std::for_each(vec.begin(), vec.end(), [&](int v){ cout << v << ":" << out++ << endl;});
	cout << endl;

	// out is reference other is value
	std::for_each(vec.begin(), vec.end(), [=, &out](int v){ cout << v << ":" << out++ << endl;});
	cout << endl;

	std::for_each(vec.begin(), vec.end(), [](int & v){ cout << v++ << ":"; cout << v << endl;});
	cout << endl;

	int in = 10;
	std::for_each(vec.begin(), vec.end(), [in, &out](int v){ cout << v << ":" << in << ":" << out++ << endl;});
	cout << endl;

	return 0;
}

