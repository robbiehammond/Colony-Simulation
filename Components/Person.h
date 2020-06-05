#pragma once
#include <SFML/Graphics.hpp>
#include "Colony.h"
#include "Map.h"


class Person
{
public:
	Person(float startX, float startY, Colony _col, Map _curMap);
	sf::Color color;
	sf::Vector2f position;
	sf::CircleShape shape;

	//idea for later maybe - if I give them all unique names, it would be pretty cool to be able to reference who got diseased and for the player to know what's going on. To give each person a name, maybe create a large array of strings storing possible names, and the program just chooses a random one. Don't know how this might affect runtime though. If I just fill the array at the very start, it might be okay actually, since arrays are random access. 
	string name;

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
	bool generateDisease(); //bool to return if the person actually got the disease or not 
	void setDiseaseEffects();
	void spreadDisease(Person& other);
	//make random animal spawns (just to get their positions different)

private:
	//TODO - make a list of names that ISN'T recreated each and every time a new person is made. Miss with that
	
};
