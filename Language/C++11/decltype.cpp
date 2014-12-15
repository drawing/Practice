#include <iostream>
#include <vector>

using namespace std;

int main()
{
	vector<int> vec;
	vec.push_back(1);

	auto i = vec.begin();
	decltype(i) j = vec.end();

	return 0;
}

