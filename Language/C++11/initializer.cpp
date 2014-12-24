#include <vector>
#include <set>
#include <iostream>

int main()
{
	std::vector<int> vec = {1, 2, 3, 4};
	for (auto k : vec) {
		std::cout << k << " ";
	}
	std::cout << std::endl;

	std::set<int> st = {1, 2, 3, 4};
	return 0;
}
