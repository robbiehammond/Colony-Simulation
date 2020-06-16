#include "SandboxMode.h"
#include <iostream>

Colony redCol(sf::Color::Red);
Colony greenCol(sf::Color::Green);
Colony blueCol(sf::Color::Blue);

SandboxMode::SandboxMode(sf::RenderWindow& _window, sf::Font& _font, Map _map)
	: window(_window), font(_font), map(_map), button(_window, _font)
{
	playGame();
}

Person& SandboxMode::findClose(Person& prim)
{
	Person placeholder(-10000, -100000, prim.myCol, prim.curMap);

	float curMinDist = 400; //settable min detection distance

	Person* saveNode = &prim;

	for (auto i = 0; i < ar.size(); i++) {
		const float curNodeDist = prim.distance(ar[i]);
		if (curNodeDist < curMinDist && curNodeDist != 0) {
			saveNode = &ar[i];
			break;
		}
	}
	if (saveNode->shape.getPosition() == prim.shape.getPosition()) {
		return placeholder;
	}
	else
		return *saveNode;
}

void SandboxMode::mutate(Person& person)
{
	int random = 1 + (rand() % 1000);
	//mutation 1: get healthier
	if (random == 500)
	{
		person.updateHealth(person.radius + 1);
	}
	//mutation 2: get stronger
	if (random == 501) {
		person.damage += 1;
	}
}

void SandboxMode::fillAr(int x, int y, Colony col)
{
	Person p(x, y, col, map.m);
	if (p.myCol.color == sf::Color::Yellow) {
		p.damage = 20;
		p.updateHealth(40);
	}
	//make sure they're being filled in a correct map range
	if (p.checkBounds(p.position.x, p.position.y)) {
		ar.push_back(p);
	}
}

void SandboxMode::moveNode(Person& prim, Person& closest)
{
	float dist = prim.distance(closest);
	//move if the close node isn't prim, it's within 1000 units, and it has a different color
	if (dist != 0 && dist < 1000 && prim.myCol.color != closest.myCol.color) {
		moveTowardNode(prim, closest);
	}
	//otherwise, just go to the center 
	else
	{
		prim.moveToCenter();
	}
}


void SandboxMode::updateNodes(sf::RenderWindow& window, sf::Time& elapsed_time)
{
	if (!ar.empty()) {
		for (auto& i : ar)
		{
			if (elapsed_time.asMilliseconds() % 100 == 0) {
				//you'll soon be a pointer to the reference of findNode
				Person* p = &findClose(i);
				mutate(i);
				moveNode(i, *p);
			}
			move(i);
			window.draw(i.shape);
		}
	}
}

bool SandboxMode::detectExitClick(ExitButton button)
{
	sf::Vector2f mouseCoords = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	sf::FloatRect bound = button.outline.getGlobalBounds();
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && bound.contains(mouseCoords))
		return true;
	else
		return false;
}

void SandboxMode::getUserInput(sf::RenderWindow& window, sf::Event& event)
{
	if (event.type == sf::Event::Closed)
	{
		window.close();
	}

	//don't allow the number of people on the board to exceed 500
	if (ar.size() <= 500) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i pos = sf::Mouse::getPosition(window);
			fillAr(pos.x, pos.y, redCol);
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			sf::Vector2i pos = sf::Mouse::getPosition(window);
			fillAr(pos.x, pos.y, greenCol);
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
		{
			sf::Vector2i pos = sf::Mouse::getPosition(window);
			fillAr(pos.x, pos.y, blueCol);
		}
	}

	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::A)
		{
			cout << ar.size() << endl;
		}
	}
}


void SandboxMode::playGame()
{
	sf::Texture maptext;
	maptext.loadFromFile(map.to_string());
	sf::Sprite map(maptext);

	sf::Clock r;
	sf::Time elapsed_time;

	while (window.isOpen() && !detectExitClick(button))
	{

		elapsed_time += r.restart();
		sf::Event event;

		while (window.pollEvent(event))
		{
			getUserInput(window, event);
		}

		window.clear();

		
		window.draw(map);
		drawExitButton(button);

		//update game 
		updateNodes(window, elapsed_time);
		window.display();

		//after the display
		removeAndShuffle(elapsed_time);
	}
	//on close
	ar.clear();

}
