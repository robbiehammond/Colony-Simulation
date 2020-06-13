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

	string name;

	Colony myCol;

	bool isDiseased;
	float radius;
	int health;
	float defaultSpeed = 0.2f;
	int damage;
	Map curMap;

	float upSpeed;
	float downSpeed;
	float rightSpeed;
	float leftSpeed;
	bool weatherEffectsSet = false;

	float distance(Person& other);
	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();

	void moveToCenter();
	void updateRadius(float _radius);
	void updateHealth(float _health);
	void updateSpeed(float _speed);
	bool checkBounds(float x, float y);
	bool generateDisease(); //bool to return if the person actually got the disease or not 
	void setDiseaseEffects();
	bool spreadDisease(Person& other);
	bool recoverFromDisease();
	void sufferDiseaseEffects();
	void assignName(string assignedName);
	void resetSpeed();

private:
	//TODO - make a list of names that ISN'T recreated each and every time a new person is made. Miss with that
	
};
