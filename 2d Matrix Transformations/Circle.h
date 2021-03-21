#pragma once

#include "Shape.h"

namespace trans {
	class Circle : public Shape
	{
	private:
		float radius;
	public:
		Circle(float,float,float);
		void initialize();
	};
}


