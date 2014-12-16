#include <iostream>

using namespace std;

class Shape {
public:
	virtual void draw() {
		cout << "draw one shape" << endl;
	};
	virtual ~Shape() {}
};

class Circle : public Shape {
public:
	void draw() override {
		cout << "draw one circle" << endl;
	}
};

// complie failed
/**
class Triangle : public Shape {
public:
	virtual void draw(int) override {
		cout << "draw one Triangle" << endl;
	}
};
*/

int main()
{
	Shape * shape = new Circle();

	shape->draw();

	delete shape;

	return 0;
}

