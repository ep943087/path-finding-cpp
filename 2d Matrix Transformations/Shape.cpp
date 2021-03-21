#include "Shape.h"

namespace trans {
	Shape::~Shape() {
		delete points;
	}

	int Shape::getSize() {
		return size;
	}

	Point* Shape::getPoints() {
		return points;
	}

	void Shape::translate(float x, float y) {
		for (int i = 0;i < size;i++) {
			points[i].x += x;
			points[i].y += y;
		}
	}

	void Shape::rotate(float angle, Point p) {
		float ax[2][2] = {
			{cos(angle),-sin(angle)},
			{sin(angle),cos(angle) }
		};

		float x, y;
		for (int i = 0;i < size;i++) {
			x = points[i].x - p.x;
			y = points[i].y - p.y;
			points[i].x = ax[0][0] * x + ax[0][1] * y + p.x;
			points[i].y = ax[1][0] * x + ax[1][1] * y + p.y;
		}
	}
}