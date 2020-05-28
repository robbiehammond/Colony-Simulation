#include <iostream>
#include <SFML/Window.hpp>
#include "Person.h"
#include "Colony.h"
#include "Map.h"
#include "TitleScreen.h"
#include "SandboxMode.h"
#include "ConflictMode.h"

//the selected Game mode
Mode selectedMode;

//the selected map
Map theMap(Map0);

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "My window", sf::Style::Close);
	sf::Font font;
	font.loadFromFile("arial.ttf"); //choose a more interesting font later
	

	//maybe do a while (selectedMode != exit) type thing here
	TitleScreen title(window, font);
	selectedMode = title.getSelectedMode();
	theMap = title.getChosenMap();

	sf::sleep(sf::milliseconds(250));

	if (selectedMode == Sandbox)
		SandboxMode sandbox(window, font, theMap);
	if (selectedMode == Conflict)
		ConflictMode conflict(window, font, theMap);
}