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

//put this in colony class - maybe not do this on each iteration bc its costly
void findClose(Person& prim)
{
	vector<sf::Vector2f> locations;
	sf::Vector2f vec;
	for (int i = 0; i < ar.size(); i++)
	{
		sf::Vector2f vec = ar[i].position;
		locations.push_back(vec);
	}
	/*
	for (int i = 0; i < locations.size(); i++)
	{
		cout << locations[i].x << " " << locations[i].y << "\t";
	}
	cout << endl;
	*/
}


int main()
{
	Person p(sf::Color::Green, 100, 100);
	ar.push_back(p);
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

		

		findClose(p);
		
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