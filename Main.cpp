#include <iostream>
#include <SFML/Window.hpp>
#include "Person.h"

using namespace std;

void moveTo(Person &p, int x, int y)
{
	p.shape.setPosition(x, y);
}


int main()
{
	Person p(3, sf::Color::Green);
	sf::RenderWindow window(sf::VideoMode(1280, 720), "My window");
	

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			
			
			if (event.type == sf::Event::KeyPressed)
			{
				sf::Vector2f pos = p.shape.getPosition();
				int x = pos.x;
				int y = pos.y;
				moveTo(p, x + 10, y);
				cout << x;
			
			}
			
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			window.clear();
			window.draw(p.shape);
			window.display();
			
		}
	}
	return 0;
}