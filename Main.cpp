#include <iostream>
#include <stdlib.h>
#include <SFML/Window.hpp>
#include "Person.h"

using namespace std;

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


int main()
{
	Person p(sf::Color::Red);
	Person w(sf::Color::Magenta);
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
		}
		window.clear();
		move(p);
		move(w);
		window.draw(p.shape);
		window.draw(w.shape);
		window.display();

	}
	return 0;
}