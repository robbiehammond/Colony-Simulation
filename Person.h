#pragma once
#include <SFML/Graphics.hpp>
#ifndef PERSON
#define PERSON

class Person
{
public:
	Person(int initRad, sf::Color initColor);
	int rad;
	int x;
	int y;
	sf::Color color;
	sf::CircleShape shape;
	
};
#endif
