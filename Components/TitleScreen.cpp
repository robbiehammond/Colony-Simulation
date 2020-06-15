#include "TitleScreen.h"
#include <iostream>
#pragma once


TitleScreen::TitleScreen(sf::RenderWindow& _window, sf::Font& _font)
	: projectDesc("A fun quarantine project by Robbie Hammond\n"
		"https://github.com/robbiehammond/Simulation", _font), window(_window), font(_font), mapChosen(Map0)
{
	projectDesc.setCharacterSize(10);
	projectDesc.setPosition(1060, 690);

	title.setString("Colony Simulator");
	title.setFont(font);
	title.setPosition(450, 25);
	title.setCharacterSize(50);
	title.setFillColor(sf::Color::White);

	loadScreen();
}

sf::RectangleShape TitleScreen::createMapBox(float x, float y)
{
	sf::RectangleShape box(sf::Vector2f(100, 100));
	box.setPosition(x, y);
	box.setOutlineColor(sf::Color::White);
	box.setOutlineThickness(2);
	box.setFillColor(sf::Color::Black);
	return box;
}

sf::Text TitleScreen::createBoxText(string text, float x, float y)
{
	sf::Text tex(text, font);
	tex.setPosition(x, y);
	return tex;
}

sf::Texture TitleScreen::getMapImages(string imgPath)
{
	sf::Texture mapTex;
	mapTex.loadFromFile(imgPath);
	return mapTex;
}

sf::Sprite TitleScreen::createMapImages(sf::Texture& tex, float x, float y)
{
	sf::Sprite mapSprite(tex);
	mapSprite.setPosition(x, y);
	//an optimal scale found through trial and error
	mapSprite.setScale(.075, .12);
	return mapSprite;
}

sf::RectangleShape TitleScreen::createOtherBox(float x, float y, float width, float height, sf::Color color)
{
	sf::RectangleShape box(sf::Vector2f(width, height));
	box.setPosition(x, y);
	box.setOutlineColor(color);
	box.setOutlineThickness(2);
	box.setFillColor(sf::Color::Black);
	return box;
}

sf::Text TitleScreen::createOtherText(float x, float y, float size, sf::Color color, string tex)
{
	sf::Text words(tex, font);
	words.setPosition(sf::Vector2f(x, y));
	words.setFillColor(color);
	words.setCharacterSize(size);
	return words;
}

bool TitleScreen::clickInRange(sf::RectangleShape& object)
{
	sf::Vector2f mouseCoords = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	sf::FloatRect bound = object.getGlobalBounds();
	//if a left click occured and it's within the bounds of the object, the click was in range. Otherwise, it was not 
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && bound.contains(mouseCoords))
		return true;
	else 
		return false;
}

//sets the color of the map boxes based on which one was last clicked. Used to show which map has been selected
void TitleScreen::setColorOnClick(sf::RectangleShape& box0, sf::RectangleShape& box1, sf::RectangleShape& box2, sf::RectangleShape& box3)
{
	if (clickInRange(box0)) {
		mapChosen = Map0;
		box0.setOutlineColor(sf::Color::Blue);
		box1.setOutlineColor(sf::Color::White);
		box2.setOutlineColor(sf::Color::White);
		box3.setOutlineColor(sf::Color::White);
	}
	if (clickInRange(box1)) {
		mapChosen = Map1;
		box0.setOutlineColor(sf::Color::White);
		box1.setOutlineColor(sf::Color::Blue);
		box2.setOutlineColor(sf::Color::White);
		box3.setOutlineColor(sf::Color::White);
	}
	if (clickInRange(box2)) {
		mapChosen = Map2;
		box0.setOutlineColor(sf::Color::White);
		box1.setOutlineColor(sf::Color::White);
		box2.setOutlineColor(sf::Color::Blue);
		box3.setOutlineColor(sf::Color::White);
	}
	if (clickInRange(box3)) {
		mapChosen = Map3;
		box0.setOutlineColor(sf::Color::White);
		box1.setOutlineColor(sf::Color::White);
		box2.setOutlineColor(sf::Color::White);
		box3.setOutlineColor(sf::Color::Blue);
	}
}

Map TitleScreen::getChosenMap()
{
	return mapChosen;
}

Mode TitleScreen::getSelectedMode()
{
	return selectedMode;
}

//the equivalent of playGame() for the title screen
void TitleScreen::loadScreen()
{
	sf::RectangleShape map0box = createMapBox(400, 100);
	sf::Text map0text = createBoxText(" Map 0", 400, 200);

	sf::RectangleShape map1box = createMapBox(780, 100);
	sf::Text map1text = createBoxText(" Map 1", 780, 200);
	sf::Texture map1texture = getMapImages("Map1.png");
	sf::Sprite map1sprite = createMapImages(map1texture, 780, 100);

	sf::RectangleShape map2box = createMapBox(400, 300);
	sf::Text map2text = createBoxText(" Map 2", 400, 400);
	sf::Texture map2texture = getMapImages("Map2.png");
	sf::Sprite map2sprite = createMapImages(map2texture, 400, 305);
	
	sf::RectangleShape map3box = createMapBox(780, 300);
	sf::Text map3text = createBoxText(" Map 3", 780, 400);
	sf::Texture map3texture = getMapImages("Map3.png");
	sf::Sprite map3sprite = createMapImages(map3texture, 780, 305);


	sf::RectangleShape conflictBox = createOtherBox(910, 500, 270, 50, sf::Color::Red);
	sf::Text conflictText = createOtherText(910, 500, 30, sf::Color::Red, " Play Conflict Mode");
	sf::RectangleShape sandboxBox = createOtherBox(100, 500, 270, 50, sf::Color::Green);
	sf::Text sandboxText = createOtherText(100, 500, 30, sf::Color::Green, "Play Sandbox Mode");
	sf::RectangleShape aboutBox = createOtherBox(590, 500, 100, 50, sf::Color::Blue);
	sf::Text aboutText = createOtherText(600, 500, 30, sf::Color::Blue, "About");

	//once playingGame is true, we break this loop to move onto the actual game 
	bool playingGame = false;

	while (window.isOpen() && !playingGame) {

		sf::Event event;
		while (window.pollEvent(event)) {
			//if one of the modes has been clicked, play that mode
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (clickInRange(sandboxBox))
			{
				playingGame = true;
				selectedMode = Sandbox;
			}
			if (clickInRange(conflictBox))
			{
				playingGame = true;
				selectedMode = Conflict;
			}
			if (clickInRange(aboutBox)) 
			{
				playingGame = true;
				selectedMode = About;
			}

		setColorOnClick(map0box, map1box, map2box, map3box);

		}
		window.clear();

		//draw everything to the screen

		window.draw(map0box);
		window.draw(map0text);
		//no sprite for map0 bc the map itself is just blank

		window.draw(map1box);
		window.draw(map1text);
		window.draw(map1sprite);

		window.draw(map2box);
		window.draw(map2text);
		window.draw(map2sprite);

		window.draw(map3box);
		window.draw(map3text);
		window.draw(map3sprite);

		window.draw(projectDesc);
		window.draw(title);

		window.draw(conflictBox);
		window.draw(conflictText);
		window.draw(sandboxBox);
		window.draw(sandboxText);
		window.draw(aboutBox);
		window.draw(aboutText);

		window.display();
	}
}
