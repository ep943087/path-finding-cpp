#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Shape.h"

namespace trans {
	class Transformations
	{
	private:
		float scale;
		Point camera, anchor, oM, oC;
		bool mouseDown;
		sf::RenderWindow* window;
	public:
		Transformations(sf::RenderWindow*,float,Point,Point);
		static float getDistance(Point, Point);
		static float getAngle(Point, Point);
		Point transformPoint(Point*);
		void moveCamera(float,float);
		void setCamera(float, float);
		void setAnchor(float, float);
		void setScale(float);
		void moveScale(float);
		void handleEvents();
		Point screenToWorld(Point);
		sf::VertexArray transform(Shape*);
		void drawShape(Shape*, sf::Color*);
		void drawShapeNoFill(Shape*, sf::Color*);
	};
}



