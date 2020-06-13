#include "GameMode.h"
#include <iostream>




string GameMode::sfColorToString(sf::Color color)
{
	//can't use a switch statement unfortunately 
	if (color == sf::Color::Red)
		return "Red";
	else if (color == sf::Color::Blue)
		return "Blue";
	else if (color == sf::Color::Green)
		return "Green";
	else if (color == sf::Color::Yellow)
		return "Yellow";
	else if (color == sf::Color::White)
		return "White";
	else
		return "[Invalid Game Color Input]";
}

void GameMode::move(Person& p)
{
	int random = 1 + (rand() % 4);
	switch (random) {
	case 1:
		p.moveUp();
		break;
	case 2:
		p.moveDown();
		break;
	case 3:
		p.moveLeft();
		break;
	case 4:
		p.moveRight();
		break;
	}
}


//unlike the other findClose function where a placeholder could be returned, this one always makes finds and moves a node towards another one as long as there are more nodes of different colors left on the screen
bool GameMode::findHardClose(Person& prim)
{

	Person placeholder(-10000, -100000, prim.myCol, prim.curMap);

	float curMinDist = 2000;

	Person* saveNode = &prim;

	for (auto i = 0; i < ar.size(); i++) {
		const float curNodeDist = prim.distance(ar[i]);
		if (curNodeDist < curMinDist && curNodeDist != 0 && ar[i].myCol.color != prim.myCol.color) {
			saveNode = &ar[i];
			break;
		}
	}
	//if we return ourselves, there is no one around 
	if (saveNode->shape.getPosition() == prim.shape.getPosition()) {
		return false;
	}
	//extra logic to make sure other nodes are found, if there are other nodes on the game board
	else {
		Person closest = *saveNode;
		int dist = prim.distance(closest);
		if (dist != 0 && dist < 1000 && prim.myCol.color != closest.myCol.color) {
			moveTowardNode(prim, closest);
		}
	}
	return true;
}

//this could go in person class, but I'll leave that for if I feel like doing it later 
void GameMode::moveTowardNode(Person& prim, Person& closest)
{
	int i = 0;
	while (i < 3) {
		float dx = closest.position.x - prim.position.x;
		float dy = closest.position.y - prim.position.y;
		if (dx > 0)
			prim.moveRight();
		if (dx < 0)
			prim.moveLeft();
		if (dy > 0)
			prim.moveDown();
		if (dy < 0)
			prim.moveUp();
		if (prim.shape.getGlobalBounds().intersects(closest.shape.getGlobalBounds()) && closest.shape.getPosition() != prim.shape.getPosition()) {
			prim.updateHealth(prim.health - closest.damage);
			if (prim.damage > 1)
				prim.damage -= 1;
			closest.updateHealth(closest.health - 1);
		}
		i++;
	}
}

void GameMode::drawStatusBar(StatusBar& s)
{
	s.window.draw(s.outline);
	s.window.draw(s.displayedText);
}

void GameMode::updateStatusBar(StatusBar& bar, string s)
{
	bar.displayedText.setString(s);
}

void GameMode::drawExitButton(exitButton& button)
{
	button.window.draw(button.outline);
	button.window.draw(button.closeText);
}



StatusBar::StatusBar(sf::RenderWindow& _window, sf::Font& _font)
	: outline(sf::Vector2f(450, 25)), window(_window), font(_font)
{
	outline.setPosition(sf::Vector2f(415, 0));
	outline.setFillColor(sf::Color::Black);
	outline.setOutlineColor(sf::Color::White);
	outline.setOutlineThickness(2);

	displayedText.setPosition(415, 0);
	displayedText.setFont(font);
	displayedText.setCharacterSize(20);
	displayedText.setString("Place your 4 spawners where you'd like");
}

exitButton::exitButton(sf::RenderWindow& _window, sf::Font& _font)
	: outline(sf::Vector2f(25, 25)), window(_window), font(_font)
{
	outline.setPosition(sf::Vector2f(1255, 0));
	outline.setFillColor(sf::Color::Black);
	outline.setOutlineColor(sf::Color::White);
	outline.setOutlineThickness(2);
	
	closeText.setPosition(sf::Vector2f(1255, 0));
	closeText.setFont(font);
	closeText.setCharacterSize(20);
	closeText.setString(" X"); //space there for formatting 
}

