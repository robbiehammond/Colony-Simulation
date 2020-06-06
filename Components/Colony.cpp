#include <SFML/Graphics.hpp>
#include "Colony.h"

Colony::Colony(sf::Color _color)
{
	color = _color;
}

//unfortunately, SFML colors don't seem to have any built-in way to convert their values into basic strings
string Colony::to_string()
{
	if (color == sf::Color::Red)
		return "Red";
	else if (color == sf::Color::Blue)
		return "Blue";
	else if (color == sf::Color::Green)
		return "Green";
	else if (color == sf::Color::Yellow)
		return "Yellow";
	//any other colony is an animal
	else
		return "Animal";

}
