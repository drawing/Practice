#ifndef SHAPE_H
#define SHAPE_H

class Shape {
public:
	virtual void draw() = 0;
};

class Painter {
public:
	void drawShape(Shape * shape);
};

#endif // SHAPE_H

