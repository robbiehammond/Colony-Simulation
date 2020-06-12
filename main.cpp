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


	Weekend Over and some good progress was made- here's what we still need to do 

	balance the mutations and diseases, so that the game is a bit more fair and things seem more random (ie it is actually entertaining to watch) (powerUps removed bc it caused too many bugs and it broke the "flow" of the gameplay) - Wednesday

	edit moving algorithm so that if the node is close to their own spawner, and a close node is detected to also be close, hone in better on it - Thursday

	generate wind! So when people move, they can go up fast, but down slow, or whatever the circumstance might be 
		Do this by making the speed value be completely directional -> upSpeed, downSpeed, leftSpeed, rightSpeed. Defualt these values are .2. The move functions will now be dependent on these values. If there's a tailwind, then the upSpeed can become .1, while the downSpeed can become .3. A neat idea to get the game going a bit more - Thursday

	make 3rd map, and make first and second map look better - Friday

	Clean up Code! - Saturday and Sunday

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