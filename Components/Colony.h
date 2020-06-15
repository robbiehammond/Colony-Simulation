#pragma once
#include <vector>
//Divide Colonies by Color, include in constructor later

using namespace std;

class Colony
{
public:
	Colony(sf::Color _color);

	//converts the SFML colors to basic strings, because the SFML library unfortunately does not have native support for it 
	string to_string();

	sf::Color color;
};
