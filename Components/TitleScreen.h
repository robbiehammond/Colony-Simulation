#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
using namespace std;

class TitleScreen {
public:
	TitleScreen(sf::RenderWindow& _window, sf::Font& _font);
	sf::Text buildTitle();
	sf::RectangleShape createMapBox(float x, float y); //might need another field for image path later, or just get rid of the space later on
	sf::Text createBoxText(string text, float x, float y);
	sf::Texture getMapImages(string imgPath);
	sf::Sprite createMapImages(sf::Texture& tex, float x, float y);
	sf::RectangleShape createOtherBox(float x, float y, float width, float height);
	void loadScreen();

private:
	sf::RenderWindow& window;
	sf::Font& font;
	sf::Text projectDesc;
	sf::Text title;

};