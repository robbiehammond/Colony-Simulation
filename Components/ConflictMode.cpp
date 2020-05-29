#include "ConflictMode.h"
#include <iostream>
#include <vector>

using namespace std;

Colony _redCol(sf::Color::Red);
Colony _greenCol(sf::Color::Green);
Colony _blueCol(sf::Color::Blue);
Colony _yellowColony(sf::Color::Yellow);
Colony _otherCol(sf::Color::White);

bool allPlaced = false;




//keep all the spawners here - 
vector<sf::RectangleShape> spawners;

ConflictMode::ConflictMode(sf::RenderWindow& _window, sf::Font& _font, Map _map)
	: window(_window), font(_font), map(_map)
{
	playGame();
}

//maybe not always have this be void 
void ConflictMode::setSpawnPoints()
{
		sf::Vector2f mouseCoords = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		sf::RectangleShape rect(sf::Vector2f(50, 50));
		rect.setPosition(mouseCoords);
		Person placehold(mouseCoords.x, mouseCoords.y, _otherCol, map);
		if (placehold.checkBounds(mouseCoords.x, mouseCoords.y)) {
			switch (spawners.size()) {
			case 0:
				rect.setFillColor(sf::Color::Red);
				sf::sleep(sf::milliseconds(200));
				spawners.push_back(rect);
				break;
			case 1:
				rect.setFillColor(sf::Color::Blue);
				sf::sleep(sf::milliseconds(200));
				spawners.push_back(rect);
				break;
			case 2:
				rect.setFillColor(sf::Color::Green);
				sf::sleep(sf::milliseconds(200));
				spawners.push_back(rect);
				break;
			case 3:
				rect.setFillColor(sf::Color::Yellow);
				sf::sleep(sf::milliseconds(200));
				spawners.push_back(rect);
				break;
			default:
				break;
			}
		}
		//rect.setFillColor(curCol.color);
}

bool ConflictMode::clickInRange(sf::RectangleShape& object)
{
	sf::Vector2f mouseCoords = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	sf::FloatRect bound = object.getGlobalBounds();
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && bound.contains(mouseCoords))
		return true;
	else
		return false;
}

void ConflictMode::getUserInput(sf::RenderWindow& window, sf::Event& event)
{
	if (event.type == sf::Event::Closed)
	{
		window.close();
	}

	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::A)
		{
			cout << ar.size() << endl;
		}
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		sf::Vector2i pos = sf::Mouse::getPosition(window);
		fillAr(pos.x, pos.y, _greenCol);
	}

}

void ConflictMode::fillAr(int x, int y, Colony col)
{
	Person p(x, y, col, map.m);
	if (p.myCol.color == sf::Color::White) {
		p.damage = 20;
		p.updateHealth(40);
	}
	//make sure they're being filled in a correct map range
	if (p.checkBounds(p.position.x, p.position.y)) {
		ar.push_back(p);
	}
}



void ConflictMode::spawn()
{
	if (allPlaced && ar.size() <= 100) {
		for (int i = 0; i < spawners.size(); i++) {
			Colony curCol(spawners[i].getFillColor());
			int random = 1 + (rand() % 100);
			int random2 = 1 + (rand() % 100);
			if (random == 50 && random2 == 14) {
				fillAr(spawners[i].getPosition().x, spawners[i].getPosition().y, curCol);
			}
		}
	}
}

void ConflictMode::findSpawner(Person& prim)
{
	int closest = 5;
	float dist = 10000;
	for (int i = 0; i < spawners.size(); i++) {
		//update, find the shape with the closest distance 
		float dx = spawners[i].getPosition().x - prim.position.x;
		float dy = spawners[i].getPosition().y - prim.position.y;
		int curDist = sqrt(dx * dx + dy * dy);
		if (curDist < dist) {
			dist = curDist;
			closest = i;
		}
	}
	if (closest != 5) {
		sf::Vector2f curScale = spawners[closest].getSize();
		float dx = spawners[closest].getPosition().x - prim.position.x;
		float dy = spawners[closest].getPosition().y - prim.position.y;
		if (dx > 0)
			prim.moveRight();
		if (dx < 0)
			prim.moveLeft();
		if (dy > 0)
			prim.moveDown();
		if (dy < 0)
			prim.moveUp();
		if (prim.shape.getGlobalBounds().intersects(spawners[closest].getGlobalBounds()) && spawners[closest].getFillColor() != prim.myCol.color) {
			curScale.x = curScale.x - 5;
			curScale.y = curScale.y - 5;
			spawners[closest].setSize(curScale);
			cout << spawners[closest].getSize().x << " " << spawners[closest].getSize().y << endl;
		}
	}

}

void ConflictMode::playGame()
{

	sf::Clock r;
	sf::Time elapsed_time;


	sf::Texture maptext;
	maptext.loadFromFile(map.to_string());
	sf::Sprite map(maptext);

	while (window.isOpen()) {
		elapsed_time += r.restart();
		sf::Event event;


		while (window.pollEvent(event)) {
			getUserInput(window, event);
		}


		window.clear();


		window.draw(map);

		if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && !allPlaced) {
			setSpawnPoints();
		}
		if (spawners.size() == 4)
			allPlaced = true;

		int spawnerSize = spawners.size();
		for (int i = 0; i < spawnerSize; i++) {
			spawn();
			if (spawners[i].getSize().x <= 0 && spawners[i].getSize().y <= 0) {
				spawners.erase(spawners.begin() + i);
				spawnerSize = spawners.size();
			}
			else
				window.draw(spawners[i]);
		}

		if (!ar.empty()) {
			for (auto& i : ar)
			{
				if (elapsed_time.asMilliseconds() % 100 == 0) {

					Person p = findClose(i);
					mutate(i);
					moveNode(i, p);
					findSpawner(i);
				}
				move(i);
				window.draw(i.shape);
			}
		}

		window.display();
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
}
