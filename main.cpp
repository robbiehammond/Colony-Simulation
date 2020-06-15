#include <iostream>
#include <SFML/Window.hpp>
#include "Person.h"
#include "Colony.h"
#include "Map.h"
#include "TitleScreen.h"
#include "SandboxMode.h"
#include "ConflictMode.h"
#include "AboutScreen.h"

//the selected Game mode
Mode selectedMode;

//the selected map
Map theMap(Map0);

int main()
{
	//the window where all the events are displayed
	sf::RenderWindow window(sf::VideoMode(1280, 720), "My window", sf::Style::Close);

	//font for all the text
	sf::Font font;
	font.loadFromFile("arial.ttf"); 

	//game loop
	//when the constructor of a given mode is called, the playGame() function is called, which calls the main game loop for that mode
	//thus, once the main game loop for that mode is broken, the program is brought back to this loop, which will just keep displaying the title screen until another mode is selected
	while (window.isOpen()) {

		TitleScreen title(window, font);
		selectedMode = title.getSelectedMode();
		theMap = title.getChosenMap();

		sf::sleep(sf::milliseconds(250));
		if (selectedMode == Sandbox) {
			SandboxMode sandbox(window, font, theMap);
		}
		if (selectedMode == About) {
			AboutScreen about(window, font);
		}
		if (selectedMode == Conflict) {
			ConflictMode conflict(window, font, theMap);
		}
		selectedMode = None;
	}
}