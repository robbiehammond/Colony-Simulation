#include <SFML/Graphics.hpp>
#include "Person.h"

using namespace std;

Person::Person(sf::Color initColor, float startX, float startY)
{
	position.x = startX;
	position.y = startY;
	color = initColor;
	shape.setPosition(position);
	shape.setFillColor(initColor);
	shape.setRadius(5);
}

sf::FloatRect Person::getPosition()
{
	return shape.getGlobalBounds();
}


void Person::moveUp()
{
	position.y -= speed;
	shape.setPosition(position);
}

void Person::moveDown()
{
	//shape.move(0, .2);
	position.y += speed;
	shape.setPosition(position);
}

void Person::moveLeft()
{
	//shape.move(-.2, 0);
	position.x -= speed;
	shape.setPosition(position);
}

void Person::moveRight()
{
	//shape.move(.2, 0);
	position.x += speed;
	shape.setPosition(position);
}


float Person::distance(Person& other)
{
	return sqrt(pow(other.position.x - this->position.x, 2) + pow(other.position.y - this->position.y, 2) * 1.0);
}



