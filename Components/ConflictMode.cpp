#include "ConflictMode.h"
#include <iostream>
#include <fstream>
#include <vector>

/*
global event possibilities
-whenever a spawner is removed - finished
-whenever all members of a colony die - fininshed 
-whenever a powerup is placed on the board - yep fuck that 
*/
using namespace std;

//colonies and a bool values for displayed messages 
Colony _redCol(sf::Color::Red); //index 1
bool redColAlive = true;
bool redDeathMessageDisplayed = false;

Colony _greenCol(sf::Color::Green); //index 2
bool greenColAlive = true;
bool greenDeathMessageDisplayed = false;

Colony _blueCol(sf::Color::Blue); //index 3
bool blueColAlive = true;
bool blueDeathMessageDisplayed = false;

Colony _yellowColony(sf::Color::Yellow); //index 4
bool yellowColAlive = true;
bool yellowDeathMessageDisplayed = false;

bool aliveCols[] = { 1, 1, 1, 1 }; //everyone starts out alive 

//make hashmap to store indexes of colonies and the colonies 

//animals
Colony _otherCol(sf::Color::White);

bool allPlaced = false; //victory achieved 

vector<string> assignableNames; //currently 1188 size, can be increased.

vector<sf::RectangleShape> spawners; //keep all the spawners here

bool gameOver = false;


ConflictMode::ConflictMode(sf::RenderWindow& _window, sf::Font& _font, Map _map)
	: window(_window), font(_font), map(_map), bar(_window, _font), button(_window, _font)
{
	fillNameArray();
	playGame();
}

//fills the name array from the name file 
void ConflictMode::fillNameArray()
{
	string curline;
	ifstream nameFile("Assignable Names.txt");
	if (nameFile.is_open()) {
		while (getline(nameFile, curline)) {
			assignableNames.push_back(curline);
		}
		nameFile.close();
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

	//points to a close (but not necessarily closest) node. Starts of as the current node that's searching.
	Person* saveNode = &prim;

	for (auto i = 0; i < ar.size(); i++) {
		const float curNodeDist = prim.distance(ar[i]);
		//if this node is close enough to be found and this node isn't itself, continue
		if (curNodeDist < curMinDist && curNodeDist != 0 && prim.myCol.color != ar[i].myCol.color) {
			//if they're the same color, possibly spread disease
			if (prim.myCol.color == ar[i].myCol.color) {
				int random = 1 + (rand() % 20);
				if (random == 1) {
					if (prim.spreadDisease(ar[i])) {
						updateStatusBar(bar, prim.name + " spread disease to " + ar[i].name);
					}
				}
			}
			//the close node is now an actual close node, and not just the searching node
			saveNode = &ar[i];
			break;
		}
	}
	//if we didn't find a close one and the close one is just this one, return a node out of bounds - other methods will interpret this 
	if (saveNode->shape.getPosition() == prim.shape.getPosition()) {
		return placeholder;
	}
	else
		return *saveNode;
}


//if a spawner is close (maybe within 50?), ignore all other nodes and go to spawner 
bool ConflictMode::otherSpawnerClose(Person& prim)
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

//ununsed for now, but might not always be that way
bool ConflictMode::ourSpawnerClose(Person& prim)
{
	int x = prim.shape.getPosition().x;
	int y = prim.shape.getPosition().y;
	for (unsigned i = 0; i < spawners.size(); i++) {
		//need to be a bit closer to our own spawner in order to return true
		//let's start with 50 and see how it goes
		if (abs(spawners[i].getPosition().x - x) < 25 && abs(spawners[i].getPosition().y - y) < 25 && spawners[i].getFillColor() == prim.myCol.color) {
			cout << prim.name + " from " + sfColorToString(prim.myCol.color) + " was close enough to their spawner" << endl;
			return true;
		}
	}
	return false;
}

//this works, but it's kinda ugly
void ConflictMode::checkIfColonyIsAlive()
{
	//death messages are still true for some reason
	bool redSpawnerFound = false;
	bool greenSpawnerFound = false;
	bool blueSpawnerFound = false;
	bool yellowSpawnerFound = false;
	for (int i = 0; i < spawners.size(); i++) {
		if (spawners[i].getFillColor() == sf::Color::Red) 
			redSpawnerFound = true;
		else if (spawners[i].getFillColor() == sf::Color::Green)
			greenSpawnerFound = true;
		else if (spawners[i].getFillColor() == sf::Color::Blue)
			blueSpawnerFound = true;
		else if (spawners[i].getFillColor() == sf::Color::Yellow)
			yellowSpawnerFound = true;
	}

	if (!redSpawnerFound && !redColAlive && !redDeathMessageDisplayed) {
		updateStatusBar(bar, "Red Colony is Eliminated!");
		redDeathMessageDisplayed = true;
		aliveCols[0] = 0;
	}
	else if (!greenSpawnerFound && !greenColAlive && !greenDeathMessageDisplayed) {
		updateStatusBar(bar, "Green Colony is Eliminated!");
		greenDeathMessageDisplayed = true;
		aliveCols[1] = 0;
	}
	else if (!blueSpawnerFound && !blueColAlive && !blueDeathMessageDisplayed) {
		updateStatusBar(bar, "Blue Colony is Eliminated!");
		blueDeathMessageDisplayed = true;
		aliveCols[2] = 0;
	}
	else if (!yellowSpawnerFound && !yellowColAlive && !yellowDeathMessageDisplayed) {
		updateStatusBar(bar, "Yellow Colony is Eliminated!");
		yellowDeathMessageDisplayed = true;
		aliveCols[3] = 0;
	}
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
	bool found = false; //if a node has been found or not 
	float dist = prim.distance(closest);

	//if the closest node isn't this node, isn't extremely far away, and it has a different color, move towards it
	if (dist != 0 && dist < 1000 && prim.myCol.color != closest.myCol.color) {
		found = true;
		moveTowardNode(prim, closest);
	}
	else if (spawners.size() == 1 && spawners[0].getFillColor() != prim.myCol.color) { //only spawner on board matches doesn't this person's color 
		findSpawner(prim); //find and go to close spawner
	}
	else if (spawners.size() == 1 && spawners[0].getFillColor() == prim.myCol.color) { //and there are still other people around.
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
		p.damage = 10;
		p.updateHealth(60);
		p.speed = .5; //these animals are much faster than people too
	}
	//make sure they're being filled in a correct map range
	if (p.checkBounds(p.position.x, p.position.y)) {
		int nameIndex = rand() % assignableNames.size();
		p.assignName(assignableNames[nameIndex]);
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
					//make this a bit more complex than simply removing 5 each time it is hit. Maybe make it based on the person's strength/health?
					curScale.x = curScale.x - 5;
					curScale.y = curScale.y - 5;
					spawners[closest].setSize(curScale);
				}
				i++;
			}
		}

}

void ConflictMode::updateNodes(sf::RenderWindow& window, sf::Time& elapsed_time)
{
	bool redCurAlive = false;
	bool greenCurAlive = false;
	bool blueCurAlive = false;
	bool yellowCurAlive = false;
	if (!ar.empty()) {
		for (auto& i : ar)
		{
			//check if at least one person from a given colony is alive - if not found when looping through the entire array, the whole colony must be gone.
			if (i.myCol.color == sf::Color::Red)
				redCurAlive = true;
			else if (i.myCol.color == sf::Color::Green)
				greenCurAlive = true;
			else if (i.myCol.color == sf::Color::Blue)
				blueCurAlive = true;
			else if (i.myCol.color == sf::Color::Yellow)
				yellowCurAlive = true;

			if (elapsed_time.asMilliseconds() % 100 == 0) {
				if (otherSpawnerClose(i)) {
					findSpawner(i);
				}
				else {
					Person* p = &findClose(i); //a pointer would work better so I don't need to make a new object, but there's some bug with the SFML source code with the getPointCount function. Not too much I can do about that, but this seems to avoid the probelm 
					if (i.generateDisease())
						updateStatusBar(bar, i.name + " from " + i.myCol.to_string() + " Colony generated a disease!");
					mutate(i);	
					moveNode(i, *p); 
					findSpawner(i);
					spawnAnimal();
				}
			}
			move(i);
			window.draw(i.shape);
		}
		redColAlive = redCurAlive;
		greenColAlive = greenCurAlive;
		blueColAlive = blueCurAlive;
		yellowColAlive = yellowCurAlive;
		checkIfColonyIsAlive();

		//no need to do it crazy often, so just do it once every 1000 milliseconds
		if (elapsed_time.asMilliseconds() % 1000 == 0) {
			checkForVictory(window);
		}
	}
}

void ConflictMode::updateSpawners(sf::RenderWindow& window)
{
	int spawnerSize = spawners.size();
	for (int i = 0; i < spawnerSize; i++) {
		spawn();
		if (spawners[i].getSize().x <= 0 && spawners[i].getSize().y <= 0) {
			removeSpawner(i);
			spawnerSize = spawners.size();
		}
		else
			window.draw(spawners[i]);
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
	if (elapsed_time.asMilliseconds() % 200) {
		random_shuffle(ar.begin(), ar.end());
	}
}


bool ConflictMode::detectExitClick(exitButton button)
{
	sf::Vector2f mouseCoords = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	sf::FloatRect bound = button.outline.getGlobalBounds();
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && bound.contains(mouseCoords))
		return true;
	else
		return false;
}

void ConflictMode::removeSpawner(int spawnerIndex)
{
	string color = sfColorToString(spawners[spawnerIndex].getFillColor());
	updateStatusBar(bar, color + "'s Colony has lost their spawner!");
	spawners.erase(spawners.begin() + spawnerIndex);
}

void ConflictMode::spawnAnimal()
{
	int random = 1 + (rand() % 1000); //100000
	int random2 = 1 + (rand() % 1000);
	if (random == 1 && random2 == 1) {
		int randomX = 1 + (rand() % 1280); //maybe lower these ranges slightly later 
		int randomY = 1 + (rand() % 720);
		fillAr(randomX, randomY, _otherCol);
		updateStatusBar(bar, "An Vicious Animal Has Spawned!");
	}
}

//not working upon the second iteration of playing the game - seems like numAlive isn't going to 1 for whatever reason 
void ConflictMode::checkForVictory(sf::RenderWindow& window)
{
	int aliveIndex = 0;
	int numAlive = 0;
	for (int i = 0; i < sizeof(aliveCols) / sizeof(aliveCols[0]); i++) {
		if (aliveCols[i] == 1) {
			numAlive++;
			aliveIndex = i;
		}
		//no need to check the rest if more than 1 is alive 
		//if (numAlive > 1)
			//break;
	}
	if (numAlive == 1) {
		gameOver = true;
	}
	//cout << numAlive << endl;

}

void ConflictMode::resetGame()
{
	ar.clear();
	spawners.clear();
	allPlaced = false;
	gameOver = false;
	for (int i = 0; i < 4; i++) {
		aliveCols[i] = 1;
	}

	redColAlive = true;
	redDeathMessageDisplayed = false;

	greenColAlive = true;
	greenDeathMessageDisplayed = false;

	blueColAlive = true;
	blueDeathMessageDisplayed = false;

	yellowColAlive = true;
	yellowDeathMessageDisplayed = false;
}





void ConflictMode::playGame()
{
	sf::Clock r;
	sf::Time elapsed_time;

	sf::Texture maptext;
	maptext.loadFromFile(map.to_string());
	sf::Sprite map(maptext);

	while (window.isOpen() && !detectExitClick(button) && !gameOver) {

		elapsed_time += r.restart();
		sf::Event event;


		while (window.pollEvent(event)) {
			getUserInput(window, event);
		}
		window.clear();

		//udpating happens
		window.draw(map);

		//update status bar and button
		drawStatusBar(bar);
		drawExitButton(button);

		if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && !allPlaced)
			setSpawnPoints();
		if (spawners.size() == 4)
			allPlaced = true;

		updateSpawners(window);
		updateNodes(window, elapsed_time);

		window.display();

		//remove and shuffle
		removeAndShuffle(elapsed_time);
	}

	//if we break out of this loop bc the game is over, display which colony has won. If the game isn't over and we exit (window closed or the exit button was pressed), this code won't be executed
	if (gameOver) {
		elapsed_time = r.restart();
		sf::Text text;
		text.setFont(font);
		text.setString("This is a test"); //now we just need to find out which colony has won and then we're golden!
		text.setPosition(600, 300);
		text.setCharacterSize(30);
		text.setFillColor(sf::Color::White);
		while (elapsed_time.asSeconds() < 5) {
			elapsed_time += r.restart();
			window.clear();
			window.draw(text);
			window.display();
		}
	}

	//clear this game so the next game can start properly
	resetGame();
}