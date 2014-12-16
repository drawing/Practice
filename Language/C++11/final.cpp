#include <iostream>

using namespace std;

class Shape {
public:
	virtual void draw() final {
		cout << "draw one shape" << endl;
	};
	virtual ~Shape() {}
};

class Circle : public Shape {
public:
	// override will failed
	void draw() {
		cout << "draw one circle" << endl;
	}
};

int main()
{
	Shape * shape = new Circle();

	shape->draw();

	delete shape;

	return 0;
}

