#include <iostream>
#include <functional>

using namespace std;

void inc(int & value)
{
	value ++;
}


template<typename F, typename P>
void call(F func, P param)
{
	func(param);
}

int main()
{
	int i = 0;
	call(inc, i);
	cout << i << endl;

	call(inc, std::ref(i));
	cout << i << endl;
	return 0;
}

