#pragma once
#include <SFML/Graphics.hpp>
#include "Colony.h"
#ifndef PERSON
#define PERSON

class Person
{
public:
	Person(sf::Color initColor, float startX, float startY, Colony _col);
	sf::Color color;
	sf::Vector2f position;
	sf::CircleShape shape;
	Colony myCol;
	//eventually add?
	//bool targetFound;
	int radius;
	int health;
	float speed = 0.2f;
	int damage;

	sf::FloatRect getPosition();
	float distance(Person& other);
	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();
	

private:

	
};
#endif
