#include "Transformations.h"

namespace trans {

	Transformations::Transformations(sf::RenderWindow* window, float scale,Point camera, Point anchor) {
		this->window = window;
		this->scale = scale;
		this->camera = camera;
		this->anchor = anchor;
		mouseDown = false;
	}

	Point Transformations::transformPoint(Point* p) {
		float x = p->x - camera.x;
		float y = p->y - camera.y;

		x = x * scale + anchor.x;
		y = y * scale + anchor.y;
		Point newPoint = { x,y };
		return newPoint;
	}

	Point Transformations::screenToWorld(Point p) {
		Point p2;
		p2.x = (p.x - anchor.x) / scale + camera.x;
		p2.y = (p.y - anchor.y) / scale + camera.y;
		return p2;
	}

	void Transformations::handleEvents() {
		sf::Event event;

		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window->close();
			}
			if (event.type == sf::Event::MouseWheelMoved && abs(event.mouseWheelScroll.delta) > 0) {
				if (event.mouseWheel.delta > 0) {
					moveScale(-1);
				}
				else{
					moveScale(1);
				}
			}

			if (event.type == sf::Event::MouseButtonPressed) {
				mouseDown = true;
				oM = { (float)event.mouseButton.x,(float)event.mouseButton.y };
				oC = screenToWorld(oM);
			}
			if (event.type == sf::Event::MouseMoved) {

				if (mouseDown) {

					trans::Point m = { (float)event.mouseMove.x, (float)event.mouseMove.y };
					trans::Point world_m = screenToWorld(m);
					setCamera(oC.x + (oC.x - world_m.x), oC.y + (oC.y - world_m.y));
				}


				trans::Point m = { (float)event.mouseMove.x, (float)event.mouseMove.y };
				trans::Point world_m = screenToWorld(m);
				setCamera(world_m.x, world_m.y);
				setAnchor(m.x, m.y);
			}

			if (event.type == sf::Event::MouseButtonReleased) {
				mouseDown = false;
			}
		}
	}

	float Transformations::getAngle(Point a, Point b) {
		return 0.0f;
	}

	float Transformations::getDistance(Point a, Point b) {
		return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
	}

	void Transformations::drawShape(Shape* shape, sf::Color* color) {
		sf::ConvexShape convex;
		convex.setPointCount(shape->getSize());
		convex.setFillColor(*color);
		Point* points = shape->getPoints();
		for (int i = 0;i < shape->getSize();i++) {
			Point p = transformPoint(&points[i]);
			convex.setPoint(i, sf::Vector2f(p.x, p.y));
		}

		window->draw(convex);
	}

	void Transformations::drawShapeNoFill(Shape* shape, sf::Color *color) {
		int size = shape->getSize();
		sf::VertexArray lines(sf::LineStrip, size + 1);
		Point* points = shape->getPoints();

		for (int i = 0;i < size;i++) {
			Point p = transformPoint(&points[i]);
			lines[i].position = sf::Vector2f(p.x,p.y);
			lines[i].color = *color;
		}

		// draw line back to original point
		lines[size].position = lines[0].position;
		lines[size].color = *color;

		window->draw(lines);
	}

	void Transformations::moveCamera(float x, float y) {
		float ch = 10 / scale;
		if (x < 0) {
			camera.x -= ch;
		}
		else if (x > 0) {
			camera.x += ch;
		}
		if (y < 0) {
			camera.y -= ch;
		}
		else if (y > 0) {
			camera.y += ch;
		}
	}
	void Transformations::setCamera(float x, float y) {
		camera.x = x;
		camera.y = y;
	}
	void Transformations::setScale(float scale) {
		this->scale = scale;
	}
	void Transformations::setAnchor(float x, float y) {
		anchor.x = x;
		anchor.y = y;
	}
	void Transformations::moveScale(float ch) {
		float change = .85f;
		if (ch < 0) {
			scale *= change;
		}
		else {
			scale /= change;
		}
	}

}