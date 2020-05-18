#include <iostream>
#include <stdlib.h>
#include <SFML/Window.hpp>
#include "Person.h"
#include "Colony.h"
#include "Map.h"

using namespace std;

//holds all active people
vector<Person> ar;

//the selected map
Map theMap(Map1);

//colonies
Colony redCol(sf::Color::Red);
Colony greenCol(sf::Color::Green);
Colony blueCol(sf::Color::Blue);
Colony placehold(sf::Color::Cyan);




//moves a person in a random direction
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

//puts a new person on the screen
void fillAr(int x, int y, Colony col)
{
	Person p(x, y, col, theMap.m);
	//make sure they're being filled in a correct map range
	if (p.checkBounds(p.position.x, p.position.y)) {
		ar.push_back(p);
	}
}




//Finds a close enemy
//Probably can be implemented better
Person findClose(Person& prim)
{
	//placeholder for when the closesst is itself
	Person placeholder(-10000, -10000, placehold, theMap.m);


	float curMinDist = 400;


	Person* saveNode = &prim;

	for (auto i = 0; i < ar.size(); i++)
	{
		const float curNodeDist = prim.distance(ar[i]);
		if (curNodeDist < curMinDist && curNodeDist != 0)
		{
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




//moves node towards a close node
void moveNode(Person& prim, Person& closest)
{
	float dist = prim.distance(closest);
	if (dist != 0 && dist < 1000 && prim.myCol.color != closest.myCol.color) {
	

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
			//collision detection
			if (prim.shape.getGlobalBounds().intersects(closest.shape.getGlobalBounds()) && closest.shape.getPosition() != prim.shape.getPosition())
			{
				prim.health -= closest.damage;
				closest.health -= 1;
			}
			i++;
		}
	}
}




//changes a persons' stats at random
void mutate(Person& person)
{
	
	int random = 1 + (rand() % 1000);
	//mutation 1: get bigger
	if (random == 500)
	{
		person.updateRadius(person.radius + 1);
		person.shape.setRadius(person.radius);
	}
}

//throw all input stuff here
void getUserInput(sf::RenderWindow& window, sf::Event& event)
{
	if (event.type == sf::Event::Closed)
	{
		window.close();
	}
	
	if (ar.size() <= 1250) {
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
			cout << ar.size();
		}
	}
}


int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "My window");

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
		if (elapsed_time.asMilliseconds() % 200)
			random_shuffle(ar.begin(), ar.end());
	}
	//on close 
	cout << "Amount of people left: " << ar.size();
	return 0;
}