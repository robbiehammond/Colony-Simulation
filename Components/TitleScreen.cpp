#include "TitleScreen.h"
#pragma once


TitleScreen::TitleScreen(sf::RenderWindow& _window, sf::Font& _font)
	: projectDesc("A fun quarantine project by Robbie Hammond\n"
		"https://github.com/robbiehammond/Simulation", _font), window(_window), font(_font)
{
	projectDesc.setCharacterSize(10);
	projectDesc.setPosition(1060, 690);
	title.setString("Colony Simulator");
	title.setFont(font);
	title.setPosition(450, 25);
	title.setCharacterSize(50);
	title.setFillColor(sf::Color::White);
}

sf::Text TitleScreen::buildTitle()
{
	return sf::Text();
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
	mapSprite.setScale(.075, .12);
	return mapSprite;
}

sf::RectangleShape TitleScreen::createOtherBox(float x, float y, float width, float height)
{
	sf::RectangleShape box(sf::Vector2f(width, height));
	box.setPosition(x, y);
	box.setOutlineColor(sf::Color::Red);
	box.setOutlineThickness(2);
	box.setFillColor(sf::Color::Black);
	return sf::RectangleShape();
}



void TitleScreen::loadScreen()
{
	sf::RectangleShape map0box = createMapBox(400, 100);
	sf::Text map0text = createBoxText(" Map 0", 400, 200);

	sf::RectangleShape map1box = createMapBox(780, 100);
	sf::Text map1text = createBoxText(" Map 1", 780, 200);
	sf::Texture map1texture = getMapImages("Map1.png"); //gotta exist in this method to actually be able to see it
	sf::Sprite map1sprite = createMapImages(map1texture, 780, 100);

	sf::RectangleShape map2box = createMapBox(400, 300);
	sf::Text map2text = createBoxText(" Map 2", 400, 400);
	sf::Texture map2texture = getMapImages("Map2.png");
	sf::Sprite map2sprite = createMapImages(map2texture, 400, 305);

	
	sf::RectangleShape map3box = createMapBox(780, 300);
	sf::Text map3text = createBoxText(" Map 3", 780, 400);
	//sf::Texture map3texture = getMapImages("Map3.png");
	//sf::Sprite map3sprite = createMapImages(map3texture, 780, 100);
	

	bool playingGame = false;
	while (window.isOpen() && !playingGame) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				playingGame = true;
			}
		}
		window.clear();
		window.draw(map0box);
		window.draw(map0text);

		window.draw(map1box);
		window.draw(map1text);
		window.draw(map1sprite);

		window.draw(map2box);
		window.draw(map2text);
		window.draw(map2sprite);

		window.draw(map3box);
		window.draw(map3text);
		//window.draw(map3sprite);

		window.draw(projectDesc);
		window.draw(title);

		window.display();
	}
}
