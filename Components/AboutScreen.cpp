#include "AboutScreen.h"

AboutScreen::AboutScreen(sf::RenderWindow& _window, sf::Font& _font)
	: window(_window), font(_font)
{
	//the actual string that shows on the screen
	text.setString("The goal of this project was not to do anything groundbreaking, but just to have fun and sharpen my C++ skills a bit.\n"
					"Certain aspects of this project could certainly be improved on (ie the searching algorithm), but overall everything works\n"
					"as I wanted to.\n"); 
	text.setFont(font);
	text.setCharacterSize(20);
	displayScreen();
}

//check if the mouse coordinates are within the boundaries of the exit button, and then return true if clicked
bool AboutScreen::detectBackClick(sf::RectangleShape buttonOutline)
{
	sf::Vector2f mouseCoords = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	sf::FloatRect bound = buttonOutline.getGlobalBounds();
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && bound.contains(mouseCoords))
		return true;
	return false;
}


void AboutScreen::displayScreen()
{
	//if true, go back to title screen
	bool backPressed = false;

	text.setPosition(sf::Vector2f(100, 100));

	//back button setup logic
	sf::RectangleShape backButton(sf::Vector2f(50, 25));
	backButton.setPosition(625, 500);
	backButton.setFillColor(sf::Color::Black);
	backButton.setOutlineColor(sf::Color::White);
	backButton.setOutlineThickness(2);

	//text inside of the back button setup logic
	sf::Text backText;
	backText.setFont(font);
	backText.setString("Back");
	backText.setPosition(628, 500);
	backText.setCharacterSize(20);

	while (window.isOpen() && !backPressed) {

		sf::Event event;
		while (window.pollEvent(event)) {
			//allows the user to close the whole window
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}


		if (detectBackClick(backButton))
			backPressed = true;


		window.clear();

		//draw everything to the window
		window.draw(text);
		window.draw(backButton);
		window.draw(backText);

		window.display();
	}
}

