
#include <iostream>
#include <vector>

using namespace std;

class Container {
public:
	int data[10];
};

int* begin(Container & c) {
	return &c.data[0];
}
int* end(Container & c) {
	return &c.data[10];
}

int main()
{
	vector<int> vec;
	vec.push_back(1);
	vec.push_back(9);
	vec.push_back(9);

	for (auto k: vec) {
		cout << k << " ";
		// will not change
		k++;
	}
	cout << endl;

	for (auto & k: vec) {
		cout << k << " ";
		// will change
		k++;
	}
	cout << endl;

	for (auto k: vec) {
		cout << k << " ";
	}


	Container c;
	for (auto k : c) {
		cout << k << " ";
	}
	cout << endl;
	cout << endl;

	return 0;
}

