#include "Balls.h"

namespace balls {

	Balls::Balls(trans::Transformations* transforms) {
		size = 100;
		this->transforms = transforms;
		srand(time(0));

		// gravitational constant
		gravitational_constant = .001f;
		init_velocity = 1;
		reset();
	}

	void Balls::reset() {
		points.clear();
		Point p = { 400,300,0,0,200,randomColor() };
		points.push_back(p);
		for (int i = 1;i < size;i++) {
			float angle = ((double)rand() / RAND_MAX) * 2 * 3.141592653f;
			float radius = 1 + 10*(double)rand() / RAND_MAX;
			float x = rand()%800;
			float y = rand()%600;
			float xv = init_velocity * cos(angle);
			float yv = init_velocity * sin(angle);
			xv = yv = 0;
			Point p = { x, y, xv, yv, radius, randomColor() };
			points.push_back(p);
		}
	}

	sf::Color Balls::randomColor() {
		int r = rand() % 6;
		switch (r) {
		case 0: return sf::Color(0x801100ff);
		case 1: return sf::Color(0xb62203ff);
		case 2: return sf::Color(0xd73502ff);
		case 3: return sf::Color(0xfc6400ff);
		case 4: return sf::Color(0xff7500ff);
		case 5: return sf::Color(0xfac000ff);
		}
	}

	void Balls::drawPoints() {
		for (int i = 0;i < points.size();i++) {
			drawPoint(points[i]);
		}
	}

	void Balls::drawPoint(Point p) {
		trans::Rectangle rect(p.x, p.y, p.radius * 2, p.radius * 2);
		trans::Circle circle(p.x, p.y, p.radius);
		transforms->drawShape(&circle, &p.color);
	}

	void Balls::update() {
		for (int i = 0;i < points.size();i++) {
			for (int j = 0;j < points.size();j++) {
				if (i == j)
					continue;
				float force = getForce(points[i], points[j]);
				float angle = getAngle(points[i], points[j]);
				points[i].xvel += force * cos(angle);
				points[i].yvel += force * sin(angle);
			}
		}
		float okay = false;
		for (int i = 0;i < points.size();i++) {
			movePoint(&points[i]);
			if (points[i].x > 0 && points[i].x < 800 && points[i].y > 0 && points[i].y < 600)
				okay = true;
		}
		if (!okay)
			reset();
	}

	void Balls::movePoint(Point* p) {
		p->x += p->xvel;
		p->y += p->yvel;
	}

	float Balls::getForce(Point a, Point b) {
		float distance = getDistance(a, b);
		if (distance <= 0)
			return 0.0f;
		return gravitational_constant * a.radius * b.radius / distance * distance;
	}

	float Balls::getAngle(Point a, Point b) {
		return atan2(b.y - a.y, b.x - a.x);
	}

	float Balls::getDistance(Point a, Point b) {
		return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
	}
}