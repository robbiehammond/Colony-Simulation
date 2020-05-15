#include <iostream>
#include <stdlib.h>
#include <SFML/Window.hpp>
#include "Person.h"

using namespace std;

//holds all active people
vector<Person> ar;

void move(Person& p)
{
	int random = 1 + (rand() % 4);
	switch (random)
	{
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

void fillAr(int x, int y)
{
	Person p(sf::Color::Red, x, y);
	ar.push_back(p);
}




int main()
{
	sf::Clock clock;
	sf::RenderWindow window(sf::VideoMode(1280, 720), "My window");	

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			
			//add people on click
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sf::Vector2i pos = sf::Mouse::getPosition(window);
				fillAr(pos.x, pos.y);
			}
			
		}
		
		window.clear();

		if (!ar.empty()) {
			for (auto& i : ar)
			{
				move(i);
				window.draw(i.shape);
			}
		}
		
		window.display();

	}
	return 0;
}