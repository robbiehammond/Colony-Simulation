#pragma once
#include <SFML/Graphics.hpp>
#ifndef PERSON
#define PERSON

class Person
{
public:
	Person(sf::Color initColor);
	sf::Color color;
	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();
	sf::CircleShape shape;
private:
	enum _Direction {Up, Down, Left, Right};
	//Animation
	sf::Time _AnimTime;
	
};
#endif
