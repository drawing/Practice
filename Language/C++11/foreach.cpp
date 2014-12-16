
#include <iostream>
#include <vector>

using namespace std;

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
	cout << endl;

	return 0;
}

