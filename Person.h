#pragma once
#include <SFML/Graphics.hpp>
#include "Colony.h"
#ifndef PERSON
#define PERSON

class Person
{
public:
	Person(float startX, float startY, Colony _col);
	//add a field for a person that's been found by this person
	sf::Color color;
	sf::Vector2f position;
	sf::CircleShape shape;
	Colony myCol;
	//eventually add?
	//bool targetFound;
	//add a "can move" variable based on the map - maybe just a list of valid coordinates
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
	void updateRadius(float radius);

private:

	
};
#endif
