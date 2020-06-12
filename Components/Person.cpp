#include <SFML/Graphics.hpp>
#include "Person.h"
#include <iostream>
using namespace std;

Person::Person(float startX, float startY, Colony _col, Map _curMap)
	: myCol(_col), curMap(_curMap.m)
{
	isDiseased = false;

	//these are mutatable
	health = 10;
	radius = health;
	damage = 1 + (rand() % 10);
	
	position.x = startX;
	position.y = startY;
	color = myCol.color;
	shape.setPosition(position);
	shape.setFillColor(color);
	shape.setRadius(radius);
	myCol = _col;

	name = ""; //to be initialized in conflict mode and left blank in sandbox mode

	upSpeed = 0.2f;
	downSpeed = 0.2f;
	leftSpeed = 0.2f;
	rightSpeed = 0.2f;

}



//checking the same bounds twice here, do it only once by using a variable
void Person::moveUp()
{
	float temp = position.y;
	temp -= defaultSpeed; //flip this to the correct stuff 
	//check if where they're trying to move is a valid position
	if (checkBounds(position.x, temp))
	{
		position.y -= upSpeed;
		shape.setPosition(position);
	}
	//if it's not, push them in perpendicular direction first 
	if (!checkBounds(position.x, temp))
	{
		if (position.x < 640) {
			position.x += rightSpeed;
			shape.setPosition(position);
		}
		else
		{
			position.x -= leftSpeed;
			shape.setPosition(position);
		}
	}
	//keep pushing them back in the opposite direction until their position is valid 
	while (!checkBounds(position.x, position.y)) {
		position.y += downSpeed;
		shape.setPosition(position);
	}
}

void Person::moveDown()
{
	float temp = position.y;
	temp += defaultSpeed;
	if (checkBounds(position.x, temp)) {
		position.y += downSpeed;
		shape.setPosition(position);
	}
	if (!checkBounds(position.x, temp))
	{
		if (position.x < 640) {
			position.x += rightSpeed;
			shape.setPosition(position);
		}
		else
		{
			position.x -= leftSpeed;
			shape.setPosition(position);
		}
	}
	
	while (!checkBounds(position.x, position.y)) {
		position.y -= upSpeed;
		shape.setPosition(position);
		
	}
}

void Person::moveLeft()
{
	float temp = position.x;
	temp -= defaultSpeed;
	if (checkBounds(temp, position.y)) {
		position.x -= leftSpeed;
		shape.setPosition(position);
	}
	if (!checkBounds(temp, position.y))
	{
		if (position.y < 360) {
			position.y += downSpeed;
			shape.setPosition(position);
		}
		else
		{
			position.y -= upSpeed;
			shape.setPosition(position);
		}
	}
	
	while (!checkBounds(position.x, position.y)) {
		position.x += rightSpeed;
		shape.setPosition(position);
		
	}
}


void Person::moveRight()
{
	
	float temp = position.x;
	temp += defaultSpeed;
	if (checkBounds(temp, position.y)) {
		position.x += rightSpeed;
		shape.setPosition(position);
	}
	if (!checkBounds(temp,position.y))
	{
		if (position.y < 360) {
			position.y += downSpeed;
			shape.setPosition(position);
		}
		else
		{
			position.y -= upSpeed;
			shape.setPosition(position);
		}
	}
		
	while (!checkBounds(position.x, position.y)) {
		position.x -= leftSpeed;
		shape.setPosition(position);
		
	}
}

void Person::moveToCenter()
{
	int i = 0;
	while (i < 3) {
		float dx = 640 - position.x;
		float dy = 360 - position.y;
		if (dx > 0)
			moveRight();
		if (dx < 0)
			moveLeft();
		if (dy > 0)
			moveDown();
		if (dy < 0)
			moveUp();
		i++;
	}

}

float Person::distance(Person& other)
{
	return sqrt(pow(other.position.x - this->position.x, 2) + pow(other.position.y - this->position.y, 2) * 1.0);
}


void Person::updateRadius(float _radius)
{
	radius = _radius;
	shape.setRadius(radius);

}

void Person::updateHealth(float _health)
{
	health = _health;
	updateRadius(health);
}

void Person::updateSpeed(float _speed)
{
	defaultSpeed = _speed;
}

//returns if the bounds are valid 
bool Person::checkBounds(float x, float y)
{
	float x_coord = position.x;
	float y_coord = position.y;
	MapSelection map = curMap.m;

	//only need to loop through x_restrictions, because x and y restrictions are the same size
	for (int i = 0; i < curMap.x_restrictions.size(); i++) {
		switch (map)
		{
		case Map1:
			if (x_coord >= std::get<0>(curMap.x_restrictions[i]) && x_coord <= std::get<1>(curMap.x_restrictions[i]) && y_coord >= std::get<0>(curMap.y_restrictions[i]) && y_coord <= std::get<1>(curMap.y_restrictions[i])) {
				return false;
			}
			break;
		case Map2:
			if (x_coord >= std::get<0>(curMap.x_restrictions[i]) && x_coord <= std::get<1>(curMap.x_restrictions[i]) && y_coord >= std::get<0>(curMap.y_restrictions[i]) && y_coord <= std::get<1>(curMap.y_restrictions[i])) {
				return false;
			}
			break;
		case Map3:
			break;
		default:
			return true;
		}
	}
	//if that for loop is skipped altogether, that means there are no restrictions, so return true bc all coordinates are valid
	return true;
}


//alter the rate at which disease spreads, bc it's a bit too fast right now 
bool Person::generateDisease()
{
	//only generate disease if they're not already diseased 
	if (!isDiseased) {
		int random = 1 + (rand() % 100000); //100000
		if (random == 1) {
			isDiseased = true;
			setDiseaseEffects();
			return true;
		}
	}
	return false;
}

void Person::setDiseaseEffects()
{ 
	if (myCol.color == sf::Color::Red) {
		sf::Color diseasedRed(100, 0, 0, 255);
		shape.setFillColor(diseasedRed);
	}
	else if (myCol.color == sf::Color::Blue) {
		sf::Color diseasedBlue(0, 0, 100, 255);
		shape.setFillColor(diseasedBlue);
	}
	else if (myCol.color == sf::Color::Green) {
		sf::Color diseasedGreen(0, 100, 0, 255);
		shape.setFillColor(diseasedGreen);
	}
	else if (myCol.color == sf::Color::Yellow) {
		sf::Color diseasedYellow(250, 240, 180, 255);
		shape.setFillColor(diseasedYellow);
	}
}

//who we spread disease to is found through ConflictMode file
//returns if the disease was successfully spread
bool Person::spreadDisease(Person& other)
{
	//if we are diseased and the other person is not diseased 
	if (isDiseased && !other.isDiseased) {
		other.isDiseased = true;
		other.setDiseaseEffects();
		return true;
	}
	return false;
}

bool Person::recoverFromDisease()
{
	int random = 1 + (rand() % 1000);
	if (isDiseased && random == 1) {
		isDiseased = false;
		if (myCol.color == sf::Color::Red)
			shape.setFillColor(sf::Color::Red);

		else if (myCol.color == sf::Color::Blue)
			shape.setFillColor(sf::Color::Blue);

		else if (myCol.color == sf::Color::Green)
			shape.setFillColor(sf::Color::Green);

		else if (myCol.color == sf::Color::Yellow)
			shape.setFillColor(sf::Color::Yellow);
		return true;
	}
	return false;
}

void Person::sufferDiseaseEffects()
{
	if (isDiseased) {
		int random = 1 + (rand() % 2);
		if (random == 1)
			updateHealth(health - .05);
		if (random == 2)
			updateSpeed(defaultSpeed - .01);
	}
}

void Person::assignName(string assignedName)
{
	name = assignedName;
}

void Person::resetSpeed()
{
	upSpeed = defaultSpeed;
	downSpeed = defaultSpeed;
	leftSpeed = defaultSpeed;
	rightSpeed = defaultSpeed;
	weatherEffectsSet = false;
}
