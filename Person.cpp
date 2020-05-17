#include <SFML/Graphics.hpp>
#include "Person.h"


using namespace std;

Person::Person(float startX, float startY, Colony _col)
	: myCol(_col)
{
	found = false;
	radius = 5;
	health = 10;
	damage = 1;
	position.x = startX;
	position.y = startY;
	color = myCol.color;
	shape.setPosition(position);
	shape.setFillColor(color);
	shape.setRadius(radius);
	myCol = _col;
}

sf::FloatRect Person::getPosition()
{
	return shape.getGlobalBounds();
}


void Person::moveUp()
{
	//if they can move there (map.can move)
	position.y -= speed;
	shape.setPosition(position);
}

void Person::moveDown()
{
	position.y += speed;
	shape.setPosition(position);
}

void Person::moveLeft()
{
	position.x -= speed;
	shape.setPosition(position);
}

void Person::moveRight()
{
	
	position.x += speed;
	shape.setPosition(position);
}


float Person::distance(Person& other)
{
	return sqrt(pow(other.position.x - this->position.x, 2) + pow(other.position.y - this->position.y, 2) * 1.0);
}

void Person::updateRadius(float _radius)
{
	radius = _radius;
}







