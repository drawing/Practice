#include "shape.h"
#include <stdio.h>

#include <unistd.h>

void Painter::drawShape(Shape * shape)
{
	for (int i = 0; i < 100; i++) {
		Param p;
		p.one = "testddd";
		p.two = "ddd";
		shape->draw(p);
		printf("call java over\n");
		sleep(1);
	}
}


