#include <SFML/Graphics.hpp>
#include "Person.h"

#include <iostream>


using namespace std;

Person::Person(float startX, float startY, Colony _col)
	: myCol(_col), curMap(Map1)
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


//Fix push-back from walls, but they're generally working
void Person::moveUp()
{
	//if they can move there (map.can move)
	float temp = position.y;
	temp -= speed;
	if (checkBounds(position.x, temp)) {
		position.y -= speed;
		shape.setPosition(position);
	}
	else
	{
		shape.setPosition(position);
	}
}

void Person::moveDown()
{
	float temp = position.y;
	temp += speed;
	if (checkBounds(position.x, temp)) {
		position.y += speed;
		shape.setPosition(position);
	}
	else
	{
		shape.setPosition(position);
	}
}

void Person::moveLeft()
{
	float temp = position.x;
	temp -= speed;
	if (checkBounds(temp, position.y)) {
		position.x -= speed;
		shape.setPosition(position);
	}
	else
	{
		shape.setPosition(position);
	}
}

void Person::moveRight()
{
	
	float temp = position.x;
	temp += speed;
	if (checkBounds(temp, position.y)) {
		position.x += speed;
		shape.setPosition(position);
	}
	else
	{
		shape.setPosition(position);
	}
}


float Person::distance(Person& other)
{
	return sqrt(pow(other.position.x - this->position.x, 2) + pow(other.position.y - this->position.y, 2) * 1.0);
}

void Person::updateRadius(float _radius)
{
	radius = _radius;
}

//returns if the bounds are valid 
bool Person::checkBounds(float x, float y)
{
	float x_coord = position.x;
	float y_coord = position.y;
	MapSelection map = curMap.m;
	switch (map)
	{
	case Map1:
		if (x_coord > std::get<0>(curMap.x_restriction) && x_coord < std::get<1>(curMap.x_restriction) && y_coord > std::get<0>(curMap.y_restriction) && y_coord < std::get<1>(curMap.y_restriction)) {
			return false;
		}
		return true;
		break;
	case Map2:
		break;
	case Map3:
		break;
	}
}








