#include <iostream>
#include <stdlib.h>
#include <SFML/Window.hpp>
#include "Person.h"
#include "Colony.h"

using namespace std;

//holds all active people
vector<Person> ar;
Colony redCol(sf::Color::Red);
Colony greenCol(sf::Color::Green);
Colony blueCol(sf::Color::Blue);



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

void fillAr(int x, int y, Colony col)
{
	Person p(col.color, x, y, col);
	ar.push_back(p);
}




//TODO Make a better algorithm for finding closest other node 
//put this in colony class - maybe not do this on each iteration bc its costly
//returns the position of the closest node
Person findClose(Person& prim)
{	

	
	//placeholder for when the closesst is itself
	Person placeholder(sf::Color::Red, -10000, -10000, redCol);

	
	float curMinDist = 10000;
	
	
	Person* saveNode = &prim;
	
	for (auto i = 0; i < ar.size(); i++)
	{
		const float curNodeDist = prim.distance(ar[i]);
		if (curNodeDist < curMinDist && curNodeDist != 0)
		{
			curMinDist = curNodeDist;
			saveNode = &ar[i];
		}
	}
	//cout << saveNode->position.x - prim.position.x << " " << saveNode->position.y - prim.position.y << endl;
	if (saveNode->shape.getPosition() == prim.shape.getPosition())
		return placeholder;
	else
		return *saveNode;
}



//this works surprisingly well
void moveNode(Person& prim)
{
	Person closest = findClose(prim);
	float dist = prim.distance(closest);
	if (dist != 0 && dist < 1000 && prim.myCol.color != closest.myCol.color) {
		int dx = closest.position.x - prim.position.x;
		int dy = closest.position.y - prim.position.y;

		if (dx > 0)
			prim.moveRight();
		if (dx < 0)
			prim.moveLeft();
		if (dy > 0)
			prim.moveDown();
		if (dy < 0)
			prim.moveUp();
	}
}



void detectColision(Person& prim)
{

	Person closest = findClose(prim);
	if (prim.shape.getGlobalBounds().intersects(closest.shape.getGlobalBounds()) && closest.shape.getPosition() != prim.shape.getPosition())
	{
		cout << "collision" << endl;
	}	
}






int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "My window");	


	sf::Clock r;
	sf::Time delta_time = sf::milliseconds(1000);
	sf::Time elapsed_time;
	while (window.isOpen())
	{
		elapsed_time += r.restart();
		sf::Event event;
		while (window.pollEvent(event))
		{
			
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			
			//make it so when clicked off screen, nothing happens
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
		window.clear();



		
		if (!ar.empty()) {
			for (auto& i : ar)
			{
				
				if (elapsed_time.asMilliseconds() % 50 == 0) {
					moveNode(i);
				}
				
				move(i);
				window.draw(i.shape);
			}
		}
		
		window.display();

	}
	return 0;
}