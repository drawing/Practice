#include <iostream>

using namespace std;

int TestFunction(int param, std::function<int(int)> fun) {
	return fun(param);
}

int main() {
	int test = 100;
	int ret = TestFunction(100, [](int p) {cout << "add:" << p << endl;return p+100;});
	cout << ret << endl;
	return 0;
}

