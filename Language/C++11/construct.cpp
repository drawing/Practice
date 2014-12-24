#include <string>
#include <iostream>

using namespace std;

class Shape {
public:
	Shape() : Shape("Default") {}
	Shape(const string & name) : name(name) {}
private:
	string name;
};

int main()
{
	return 0;
}

