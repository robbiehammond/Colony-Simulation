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

	//creates the rectangle surrounding the map pictures 
	sf::RectangleShape createMapBox(float x, float y);

	//creates the text below the map boxes
	sf::Text createBoxText(string text, float x, float y);

	//fetches the map images from the directory
	sf::Texture getMapImages(string imgPath);

	//takes a texture (which is made from the image of the map), and then puts it on a SFML sprite so it can be easily displayed
	sf::Sprite createMapImages(sf::Texture& tex, float x, float y);

	//used to create any other boxes that appear on the screen
	sf::RectangleShape createOtherBox(float x, float y, float width, float height, sf::Color color);

	//used to create any other text on the screen
	sf::Text createOtherText(float x, float y, float size, sf::Color color, string s);

	//detects if a click was in the range of a given object
	bool clickInRange(sf::RectangleShape& object);

	//sets the color of the map boxes based on which one was last clicked. Used to show which map has been selected
	void setColorOnClick(sf::RectangleShape& box0, sf::RectangleShape& box1, sf::RectangleShape& box2, sf::RectangleShape& box3);

	//get things selected on the title screen
	Map getChosenMap();
	Mode getSelectedMode();

	//the equivalent of playGame() for the title screen
	void loadScreen();


private:
	Mode selectedMode;
	sf::RenderWindow& window;
	sf::Font& font;
	sf::Text projectDesc;
	sf::Text title;
	Map mapChosen;

};