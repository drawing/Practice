#include <iostream>

using namespace std;

enum class CType {
	One, Two, Three
};

enum EType {
	One, Two, Three
};

int main()
{
	CType ctype = CType::One;
	ctype = CType::Two;

	// can not print
	// cout << ctype << endl;
	
	EType etype = EType::Two;
	int a = etype;
	cout << etype << " " << a << endl;
	return 0;
}

