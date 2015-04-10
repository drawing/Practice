#ifndef SHAPE_H
#define SHAPE_H

#include <string>

struct Param
{
	std::string one;
	std::string two;
};

class Shape {
public:
	virtual void draw(const Param & param) = 0;
	virtual ~Shape() {}
};

class Painter {
public:
	void drawShape(Shape * shape);
};

#endif // SHAPE_H

