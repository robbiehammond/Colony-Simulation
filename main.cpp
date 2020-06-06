#include <iostream>
#include <SFML/Window.hpp>
#include "Person.h"
#include "Colony.h"
#include "Map.h"
#include "TitleScreen.h"
#include "SandboxMode.h"
#include "ConflictMode.h"

//@TODO - Make to_string method for colonies to get the string format of the name of the colony (so I can put it in the status bar)
//Put button on the screen, if it is clicked, the playGame() function breaks, thus the loop in main sets the selected game to None, thus the loop continues and (theoretically) the title screen is reloaded.
//Finish over weekend? The plan is to get it to a borderline finished state at least 

/*
specific plans:
	make the to_string function in colony - finished
	confirm finding algorithm is decent, divide it into multiple functions - finished
	make a way to exit game 
	make "about" section on title screen
	make 3rd map!
	get status bar displaying important events, and make it so that it is easy to add new events to display in case I add anything in the future 
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
	while (window.isOpen()) {
		sf::Font font;
		font.loadFromFile("arial.ttf"); //choose a more interesting font later

		TitleScreen title(window, font);
		selectedMode = title.getSelectedMode();
		theMap = title.getChosenMap();

		sf::sleep(sf::milliseconds(250));
		if (selectedMode == Sandbox) {
			SandboxMode sandbox(window, font, theMap);
		}
		if (selectedMode == Conflict) {
			ConflictMode conflict(window, font, theMap);
		}
		selectedMode = None;
	}
}