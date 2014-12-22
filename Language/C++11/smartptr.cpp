/**
 * http://blogs.ejb.cc/archives/6160/cplusplu-11-smart-pointers
 */

#include <memory>
#include <iostream>

using namespace std;

class Shape {
public:
	Shape() {cout << "Create" << endl;}
	~Shape() {cout << "Destroy" << endl;}
};

void CheckWeakPtr(shared_ptr<Shape> share) {
	static weak_ptr<Shape> weak = share;
	if (auto ptr = weak.lock()) {
		cout << "Weak Locked" << endl;
	}
	else {
		cout << "Weak Expired" << endl;
	}
}

int main()
{
	cout << "Share Ptr Begin" << endl;
	{
		std::shared_ptr<Shape> share(new Shape);
		CheckWeakPtr(share);
		auto temp = share;
		temp.reset();
		CheckWeakPtr(share);
	}
	CheckWeakPtr(nullptr);
	cout << "Share Ptr End" << endl;

	cout << "Unique Ptr Begin" << endl;

	{
		std::unique_ptr<Shape> p1(new Shape);
		cout << "Check:" << p1.get() << endl;
		auto p2 = std::move(p1);
		cout << "Check:" << p1.get() << endl;
	}

	cout << "Unique Ptr End" << endl;
	return 0;
}
