
#include <iostream>

using namespace std;

class Elem {
public:
	Elem() {
		cout << "Create One Elem" << endl;
	}
	Elem(const Elem & elem) {
		cout << "Copy One Elem" << endl;
	}
};

Elem func1() {
	Elem e1;
	return std::move(e1);
}

int main()
{
	Elem result;
	result = func1();
	return 0;
}

