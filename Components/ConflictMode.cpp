#include "ConflictMode.h"
#include <iostream>
#include <fstream>
#include <vector>

//TODO - assign each person their name upon spawn so I can reference them in the global events, then finish the status bar so I can display those global events. Then think of all the global events I can display, and then display them as necessary.


using namespace std;

Colony _redCol(sf::Color::Red);
Colony _greenCol(sf::Color::Green);
Colony _blueCol(sf::Color::Blue);
Colony _yellowColony(sf::Color::Yellow);
Colony _otherCol(sf::Color::White);

bool allPlaced = false;

string assignableNames[100];


//keep all the spawners here - 
vector<sf::RectangleShape> spawners;

ConflictMode::ConflictMode(sf::RenderWindow& _window, sf::Font& _font, Map _map)
	: window(_window), font(_font), map(_map), bar(_window, _font)
{
	fillNameArray();
	playGame();
}

void ConflictMode::fillNameArray()
{
	string curline;
	ifstream nameFile("Assignable Names.txt");
	if (nameFile.is_open()) {
		int i = 0;
		while (getline(nameFile, curline)) {
			assignableNames[i] = curline;
			i++;
		}
		nameFile.close();
	}
	//just checking to make sure the names get properly assinged into the array, which it seems like it does. Success! 
	for (int i = 0; i < sizeof(assignableNames) / sizeof(assignableNames[0]); i++) {
		if (assignableNames[i].size() > 1)
			cout << assignableNames[i] << endl;
	}
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

Person ConflictMode::findClose(Person& prim)
{
	Person placeholder(-10000, -100000, prim.myCol, prim.curMap);

	float curMinDist = 400; //settable min detection distance

	Person* saveNode = &prim;

	for (auto i = 0; i < ar.size(); i++) {
		const float curNodeDist = prim.distance(ar[i]);
		if (curNodeDist < curMinDist && curNodeDist != 0) {
			if (prim.myCol.color == ar[i].myCol.color) {
				int random = 1 + (rand() % 20);
				if (random == 1) {
					prim.spreadDisease(ar[i]);
				}
			}
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

bool ConflictMode::clickInRange(sf::RectangleShape& object)
{
	sf::Vector2f mouseCoords = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	sf::FloatRect bound = object.getGlobalBounds();
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && bound.contains(mouseCoords))
		return true;
	else
		return false;
}

//if a spawner is close (maybe within 50?), ignore all other nodes and go to spawner 
bool ConflictMode::spawnerClose(Person& prim)
{
	int x = prim.shape.getPosition().x;
	int y = prim.shape.getPosition().y;
	for (unsigned i = 0; i < spawners.size(); i++) {
		if (abs(spawners[i].getPosition().x - x) < 100 && abs(spawners[i].getPosition().y - y) < 100 && spawners[i].getFillColor() != prim.myCol.color) {
			//cout << "true was found";
			return true;
		}
	}
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



//this function needs to be made into something non-spaghetti
//we're double passing addresses!
void ConflictMode::moveNode(Person& prim, Person& closest)
{
	bool found = false;
	float dist = prim.distance(closest);
	if (dist != 0 && dist < 1000 && prim.myCol.color != closest.myCol.color) {
		found = true;
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
	else if (spawners.size() == 1 && spawners[0].getFillColor() != prim.myCol.color) { //only spawner on board matches doesn't this person's color 
		findSpawner(prim); //find and go to close spawner
	}
	else if (spawners.size() == 1 && spawners[0].getFillColor() == prim.myCol.color) { //and there are still other people around
		found = findHardClose(prim);
	}
	//if none of the above happened, then found needs to be set to false to do below 
	else if (spawners.size() == 0) {
		found = false;
	}
	if (!found) { //only happens when there is no one else to kill
		prim.moveToCenter();
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
		for (unsigned i = 0; i < spawners.size(); i++) {
			Colony curCol(spawners[i].getFillColor());

			const int num = (1.0 / (2.0 * spawners[i].getSize().x)) * 10000; //100 at normal size
			int random = 1 + (rand() % num); 
			int random2 = 1 + (rand() % num);
			if (random == 5 && random2 == 5) {
				fillAr(spawners[i].getPosition().x, spawners[i].getPosition().y, curCol);
			}
		}
	}
}

void ConflictMode::findSpawner(Person& prim)
{
	int closest = 5;
	float dist = 10000;
	for (unsigned i = 0; i < spawners.size(); i++) {
		//update, find the shape with the closest distance 
		float dx = spawners[i].getPosition().x - prim.position.x;
		float dy = spawners[i].getPosition().y - prim.position.y;
		float curDist = sqrt(dx * dx + dy * dy);
		if (curDist < dist && spawners[i].getFillColor() != prim.myCol.color) {
			dist = curDist;
			closest = i;
		}
	}
	if (closest < 5) {
		sf::Vector2f curScale = spawners[closest].getSize();
		float dx = spawners[closest].getPosition().x - prim.position.x;
		float dy = spawners[closest].getPosition().y - prim.position.y;
		int i = 0;
		while (i < 2) {
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
			i++;
		}
	}

}

void ConflictMode::updateNodes(sf::RenderWindow& window, sf::Time& elapsed_time)
{
	if (!ar.empty()) {
		for (auto& i : ar)
		{
			if (elapsed_time.asMilliseconds() % 100 == 0) {
				if (spawnerClose(i)) {
					findSpawner(i);
				}
				else {
					Person p = findClose(i); //we're making a copy, maybe this is what's causing so much lag tbh 
					if (i.generateDisease()) //also generate disease should just in the mutate method 
						updateStatusBar(bar, to_string(i.health));
					mutate(i);	
					moveNode(i, p); //nullptr
					findSpawner(i);
				}
			}
			move(i);
			window.draw(i.shape);
		}
	}
}

void ConflictMode::removeAndShuffle(sf::Time& elapsed_time)
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
	if (elapsed_time.asMilliseconds() % 100) {
		random_shuffle(ar.begin(), ar.end());
	}
}



void ConflictMode::getGlobalEvents()
{

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

		//udpating happens
		window.draw(map);

		//update status bar
		drawStatusBar(bar);
		updateStatusBar(bar, to_string(ar.size())); //this isn't displayed bc it's getting overriden too fast

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

		updateNodes(window, elapsed_time);

		window.display();

		//remove and shuffle
		removeAndShuffle(elapsed_time);
	}
}
