#include <iostream>
#include <SFML/Window.hpp>
#include "Person.h"
#include "Colony.h"
#include "Map.h"
#include "TitleScreen.h"
#include "SandboxMode.h"
#include "ConflictMode.h"
#include "AboutScreen.h"

/*
specific plans:
	make the to_string function in colony - finished
	confirm finding algorithm is decent, divide it into multiple functions - finished
	make a way to exit game - finished
	make "about" section on title screen - finished
	make 3rd map!
	get status bar displaying important events, and make it so that it is easy to add new events to display in case I add anything in the future - finished
	add power-ups (if there is a powerup on the screen and it is within like 300 units, go to it - there should be a lot of them going to it at once)
	balance the mutations and diseases, so that the game is a bit more fair and things seem more random (ie it is actually entertaining to watch)
	so end goal for the weekend - be "90%" done with this whole project, so we can move onto some machine learning as soon as possible.

*/

//the selected Game mode
Mode selectedMode;

//the selected map
Map theMap(Map0);

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "My window", sf::Style::Close);
	sf::Font font;
	font.loadFromFile("arial.ttf"); //choose a more interesting font later
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