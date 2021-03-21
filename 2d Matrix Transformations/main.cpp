// 2d Matrix Transformations.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Shape.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Transformations.h"


int main()
{

    sf::RenderWindow window(sf::VideoMode(800, 600),"2d Matrix Transformations");
    trans::Rectangle rect(200, 200, 100, 100);

    trans::Point camera = { 400,300 };
    trans::Point anchor = { 400,300 };
    trans::Transformations transforms(&window, 1.0f, camera, anchor);

    while(window.isOpen()){

        window.setFramerateLimit(60);

        transforms.handleEvents();

        window.clear(sf::Color(0xd3d3d3ff));

        transforms.drawShape(&rect, &sf::Color(255, 0, 0));
        transforms.drawShapeNoFill(&rect, &sf::Color(0, 0, 0));
        trans::Point p = { 200,200 };
        rect.rotate(3.141592653f * 2.0f / 200, p);
        window.display();
    }
}
