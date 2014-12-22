#include <iostream>
#include <list>

using namespace std;

int main()
{
	std::list<int> list {1, 2, 3, 4, 5};
	cout << std::all_of(list.begin(), list.end(), [](int i) {return i > 3;}) << endl;
	cout << std::none_of(list.begin(), list.end(), [](int i) {return i > 3;}) << endl;
	cout << std::any_of(list.begin(), list.end(), [](int i) {return i > 3;}) << endl;
	return 0;
}

