#pragma once
#include <SFML/Graphics.hpp>
#include "Colony.h"
#include "Map.h"


class Person
{
public:
	Person(float startX, float startY, Colony _col, Map _curMap);

	//variables that (for the most part) aren't arbitrarily changed 
	sf::Color color;
	sf::CircleShape shape;
	string name;
	Colony myCol;
	Map curMap;

	//variables that change frequently
	sf::Vector2f position;
	bool isDiseased;
	float radius;
	int health;
	float defaultSpeed = 0.2f;
	int damage;
	bool weatherEffectsSet = false;

	//directional speeds
	float upSpeed;
	float downSpeed;
	float rightSpeed;
	float leftSpeed;

	//distance from one node to the other - simply pythagorean theorem
	float distance(Person& other);

	//move person in some specific direction 
	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();

	//gets the person's coordinates and moves them appropriately towards the center of the grid 
	void moveToCenter();

	//update a person's stats 
	void updateRadius(float _radius);
	void updateHealth(float _health);
	void updateSpeed(float _speed);

	//returns if some position is valid for some map 
	bool checkBounds(float x, float y);

	//generates disease for this person - true if the disease as generated, false if not 
	bool generateDisease(); 

	//set the color of the diseased person so they can be distinguished 
	void setDiseaseEffects();

	//spreads the disease - returns if the disease was successfully spread
	bool spreadDisease(Person& other);

	//possibly get rid of the disease and stop suffering from its effects - returns if they successfully recovered or not 
	bool recoverFromDisease();

	//take damage/loose speed if diseased 
	void sufferDiseaseEffects();

	//give this person some name
	void assignName(string assignedName);

	//put all direction speeds back to the defaultSpeed
	void resetSpeed();	
};
