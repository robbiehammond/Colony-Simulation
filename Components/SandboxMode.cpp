#include "SandboxMode.h"
#include <iostream>

Colony redCol(sf::Color::Red);
Colony greenCol(sf::Color::Green);
Colony blueCol(sf::Color::Blue);

SandboxMode::SandboxMode(sf::RenderWindow& _window, sf::Font& _font, Map _map)
	: window(_window), font(_font), map(_map)
{
	playGame();
}

void SandboxMode::fillAr(int x, int y, Colony col)
{
	Person p(x, y, col, map.m);
	//make sure they're being filled in a correct map range
	if (p.checkBounds(p.position.x, p.position.y)) {
		ar.push_back(p);
	}
}

void SandboxMode::getUserInput(sf::RenderWindow& window, sf::Event& event)
{
	if (event.type == sf::Event::Closed)
	{
		window.close();
	}

	if (ar.size() <= 1000) {
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

	while (window.isOpen())
	{

		elapsed_time += r.restart();
		sf::Event event;

		while (window.pollEvent(event))
		{
			getUserInput(window, event);
		}

		window.clear();

		window.draw(map);


		//update game 
		if (!ar.empty()) {
			for (auto& i : ar)
			{
				if (elapsed_time.asMilliseconds() % 100 == 0) {
					Person p = findClose(i);
					mutate(i);
					moveNode(i, p);
				}
				move(i);
				window.draw(i.shape);
			}
		}
		window.display();

		//after the display
		int size = ar.size();
		for (int i = 0; i < size; i++)
		{
			if (ar[i].health <= 0)
			{
				ar.erase(ar.begin() + i);
				size = ar.size();
			}
		}
		if (elapsed_time.asMilliseconds() % 400)
			random_shuffle(ar.begin(), ar.end());

	}
	//on close 
	cout << "Amount of people left: " << ar.size();

}
