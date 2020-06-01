#pragma once
#include <SFML/Graphics.hpp>
#include "Colony.h"
#include "Map.h"
#ifndef PERSON
#define PERSON

class Person
{
public:
	Person(float startX, float startY, Colony _col, Map _curMap);
	sf::Color color;
	sf::Vector2f position;
	sf::CircleShape shape;
	
	Colony myCol;

	bool isDiseased;
	float radius;
	int health;
	float speed = 0.2f;
	int damage;
	Map curMap;

	float distance(Person& other);
	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();

	void moveToCenter();
	void updateRadius(float radius);
	void updateHealth(float health);
	bool checkBounds(float x, float y);
	void generateDisease();
	void spreadDisease();
	//make random animal spawns (just to get their positions different)

private:

	
};
#endif
