#include "GameMode.h"
#include <iostream>

//because SFML has no built in toString function
string GameMode::sfColorToString(sf::Color color)
{
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

//randomly move a preson up, down, left, or right
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


//function that returns a value for if a node was found 
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

//move one node toward another one 
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

void GameMode::removeAndShuffle(sf::Time& elapsed_time)
{
	int size = ar.size();
	for (int i = 0; i < size; i++)
	{
		if (ar[i].health <= 0)
		{
			ar.erase(ar.begin() + i);
			size = ar.size();
		}
	}
	if (elapsed_time.asMilliseconds() % 400) {
		random_shuffle(ar.begin(), ar.end());
	}
}

//logic to put the status bar on the screen
void GameMode::drawStatusBar(StatusBar& s)
{
	s.window.draw(s.outline);
	s.window.draw(s.displayedText);
}

//logic to update it with events
void GameMode::updateStatusBar(StatusBar& bar, string s)
{
	bar.displayedText.setString(s);
}


//put the exit button on the screen
void GameMode::drawExitButton(ExitButton& button)
{
	button.window.draw(button.outline);
	button.window.draw(button.closeText);
}

//StatusBar constructor implementation
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

//ExitButton constructor 
ExitButton::ExitButton(sf::RenderWindow& _window, sf::Font& _font)
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

