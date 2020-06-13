#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Map.h"
#include "GameMode.h"
using namespace std;

class TitleScreen {
public:
	TitleScreen(sf::RenderWindow& _window, sf::Font& _font);
	sf::RectangleShape createMapBox(float x, float y);
	sf::Text createBoxText(string text, float x, float y);
	sf::Texture getMapImages(string imgPath);
	sf::Sprite createMapImages(sf::Texture& tex, float x, float y);
	sf::RectangleShape createOtherBox(float x, float y, float width, float height, sf::Color color);
	sf::Text createOtherText(float x, float y, float size, sf::Color color, string s);
	bool clickInRange(sf::RectangleShape& object);
	void setColorOnClick(sf::RectangleShape& box0, sf::RectangleShape& box1, sf::RectangleShape& box2, sf::RectangleShape& box3);
	Map getChosenMap();
	Mode getSelectedMode();
	void loadScreen();


private:
	Mode selectedMode;
	sf::RenderWindow& window;
	sf::Font& font;
	sf::Text projectDesc;
	sf::Text title;
	Map mapChosen;

};