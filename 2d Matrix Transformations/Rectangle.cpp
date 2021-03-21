#include "Rectangle.h"
namespace trans{
	Rectangle::Rectangle(float x, float y, float width, float height) {
		this->width = width;
		this->height = height;
		this->x = x;
		this->y = y;
		size = 4;
		initialize();
	}
	void Rectangle::initialize() {
		points = new Point[size];
		points[0] = { x - width / 2.0f, y - width / 2.0f };
		points[1] = { x + width / 2.0f, y - width / 2.0f };
		points[2] = { x + width / 2.0f, y + width / 2.0f };
		points[3] = { x - width / 2.0f, y + width / 2.0f };
	}
}