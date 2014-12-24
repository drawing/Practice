#include <vector>
#include <set>
#include <iostream>

using namespace std;

class TestInit
{
public:
	TestInit(initializer_list<int> list) {
		for (auto k : list) {
			cout << "TEST:" << k << endl;
		}
	}
};

int main()
{
	std::vector<int> vec = {1, 2, 3, 4};
	for (auto k : vec) {
		std::cout << k << " ";
	}
	std::cout << std::endl;

	std::set<int> st = {1, 2, 3, 4};

	TestInit a = {1, 3, 5, 7};
	return 0;
}
