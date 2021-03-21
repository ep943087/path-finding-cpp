#pragma once

#include "Shape.h"

namespace trans {
	class Rectangle: public Shape
	{
	private:
		float width, height;
	public:
		Rectangle(float,float,float,float);
		void initialize();
	};
}


