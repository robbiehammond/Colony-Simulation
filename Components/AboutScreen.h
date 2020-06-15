#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
class AboutScreen {
public:
	AboutScreen(sf::RenderWindow& _window, sf::Font& _font);

	//check if the mouse coordinates are within the boundaries of the exit button, and then return true if clicked
	bool detectBackClick(sf::RectangleShape buttonOutline);

	//displays the AboutScreen on the window
	void displayScreen();
private:
	sf::RenderWindow& window;
	sf::Font& font;
	sf::Text text;
};