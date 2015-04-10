#include "shape.h"


void Painter::drawShape(Shape * shape)
{
	Param p;
	p.one = "testddd";
	p.two = "ddd";
	shape->draw(p);
}


