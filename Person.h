#pragma once
#include <SFML/Graphics.hpp>
#ifndef PERSON
#define PERSON

class Person
{
public:
	Person(sf::Color initColor, float startX, float startY);
	sf::Color color;
	sf::Vector2f position;
	sf::CircleShape shape;

	sf::FloatRect getPosition();
	float distance(Person& other);
	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();
	sf::Time dt;

private:
	float speed = 0.2f;
	
};
#endif
