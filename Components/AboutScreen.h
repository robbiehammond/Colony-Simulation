#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
class AboutScreen {
public:
	AboutScreen(sf::RenderWindow& _window, sf::Font& _font);
	void displayScreen();
private:
	sf::RenderWindow& window;
	sf::Font& font;
	sf::Text text;
};