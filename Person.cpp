#include <iostream>
#include <SFML/Graphics.hpp>
#include "Person.h"

using namespace std;


Person::Person(sf::Color initColor)
{
	color = initColor;
	shape.setPosition(100, 100);
	shape.setFillColor(initColor);
	shape.setRadius(5);
}

void Person::moveUp()
{
	shape.move(0, -.05);
}

void Person::moveDown()
{
	shape.move(0, .05);
}

void Person::moveLeft()
{
	shape.move(-.05, 0);
}

void Person::moveRight()
{
	shape.move(.05, 0);
}

