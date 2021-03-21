#include "Circle.h"

namespace trans {
	Circle::Circle(float x, float y, float radius) {
		this->radius = radius;
		this->x = x;
		this->y = y;
		size = 30;
		initialize();
	}
	void Circle::initialize() {
		points = new Point[size];
		float angle;
		for (int i = 0;i < size;i++) {
			angle = 2.0f * 3.141592653f * (float)i/size;
			points[i].x = x + radius * cos(angle);
			points[i].y = y + radius * sin(angle);
		}
	}
}