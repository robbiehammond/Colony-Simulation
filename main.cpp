#include <iostream>
#include <SFML/Window.hpp>
#include "Person.h"
#include "Colony.h"
#include "Map.h"
#include "TitleScreen.h"
#include "SandboxMode.h"

//the selected map
Map theMap(Map0);

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "My window", sf::Style::Close);
	sf::Font font;
	font.loadFromFile("arial.ttf"); //choose a more interesting font later

	TitleScreen title(window, font);
	title.loadScreen();
	theMap = title.getChosenMap();
	sf::sleep(sf::milliseconds(250));
	SandboxMode sandbox(window, font, theMap);
}