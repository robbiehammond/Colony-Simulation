#include <iostream>
#include <SFML/Graphics.hpp>
#include "Person.h"

using namespace std;


Person::Person(int initRad, sf::Color initColor)
{
	rad = initRad;
	color = initColor;
	shape.setRadius(rad);
	shape.setFillColor(color);
	
}


