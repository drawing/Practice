#include <memory>
#include <iostream>

using namespace std;

int main()
{
	std::unique_ptr<int> p1(new int);
	// std::unique_ptr<int> p2 = p1;
	std::unique_ptr<int> p2 = std::move(p1);
	return 0;
}

