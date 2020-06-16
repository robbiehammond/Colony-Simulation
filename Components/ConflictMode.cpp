#include "ConflictMode.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//colonies and bool values for displayed messages 
Colony _redCol(sf::Color::Red); //index 0
bool redColAlive = true;
bool redDeathMessageDisplayed = false;

Colony _greenCol(sf::Color::Green); //index 1
bool greenColAlive = true;
bool greenDeathMessageDisplayed = false;

Colony _blueCol(sf::Color::Blue); //index 2
bool blueColAlive = true;
bool blueDeathMessageDisplayed = false;

Colony _yellowColony(sf::Color::Yellow); //index 3
bool yellowColAlive = true;
bool yellowDeathMessageDisplayed = false;

bool aliveCols[] = { 1, 1, 1, 1 }; //everyone starts out alive 

//make hashmap to store indexes of colonies and the colonies 

//animals
Colony _otherCol(sf::Color::White);

//when true, game actually starts 
bool allPlaced = false;

//names of the people. Can be increased by just adding a name to the end 
vector<string> assignableNames;

//keep all the spawners here
vector<sf::RectangleShape> spawners;

//when true, the main game loop breaks 
bool gameOver = false;

//weather affects in the game, starts out with no weather 
Weather weather;
bool weatherEffectsActive = false;


ConflictMode::ConflictMode(sf::RenderWindow& _window, sf::Font& _font, Map _map)
	: window(_window), font(_font), map(_map), bar(_window, _font), button(_window, _font)
{
	fillNameArray();
	playGame();
	weather = NoWeather;
}

void ConflictMode::drawStatusBar(StatusBar& s)
{
	s.window.draw(s.outline);
	s.window.draw(s.displayedText);
}

void ConflictMode::updateStatusBar(StatusBar& bar, string s)
{
	bar.displayedText.setString(s);
}

//StatusBar constructor implementation
StatusBar::StatusBar(sf::RenderWindow& _window, sf::Font& _font)
	: outline(sf::Vector2f(450, 25)), window(_window), font(_font)
{
	outline.setPosition(sf::Vector2f(415, 0));
	outline.setFillColor(sf::Color::Black);
	outline.setOutlineColor(sf::Color::White);
	outline.setOutlineThickness(2);

	displayedText.setPosition(415, 0);
	displayedText.setFont(font);
	displayedText.setCharacterSize(20);
	displayedText.setString("Place your 4 spawners where you'd like");
}

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

void ConflictMode::setSpawnPoints()
{
		sf::Vector2f mouseCoords = window.mapPixelToCoords(sf::Mouse::getPosition(window));

		sf::RectangleShape rect(sf::Vector2f(50, 50));
		rect.setPosition(mouseCoords);

		//placeholder person to make sure that the spawners are being put in valid locations 
		Person placehold(mouseCoords.x, mouseCoords.y, _otherCol, map);

		if (placehold.checkBounds(mouseCoords.x, mouseCoords.y)) 
		{
			//switch the color of the spawner based on the size - first spawner will be red, next will be blue, etc 
			switch (spawners.size()) {
			case 0:
				rect.setFillColor(sf::Color::Red);
				sf::sleep(sf::milliseconds(200));	//wait some milliseconds to avoid double clicks 
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
}

//find any node that is relatively close
Person& ConflictMode::findClose(Person& prim)
{
	Person placeholder(-10000, -100000, prim.myCol, prim.curMap);

	//settable min detection distance
	float curMinDist = 400;

	//points to a close (but not necessarily closest) node. Starts of as the current node that's searching.
	Person* saveNode = &prim;

	for (auto i = 0; i < ar.size(); i++) {

		const float curNodeDist = prim.distance(ar[i]);

		//if they're the same color, possibly spread disease
		if (prim.myCol.color == ar[i].myCol.color) {
			int random = 1 + (rand() % 500);
			if (random == 1) {
				if (prim.spreadDisease(ar[i])) {
					updateStatusBar(bar, prim.name + " spread disease to " + ar[i].name);
				}
			}
		}

		//if this node is close enough to be found and this node isn't itself, continue
		if (curNodeDist < curMinDist && curNodeDist != 0 && prim.myCol.color != ar[i].myCol.color) {
			//the close node is now an actual close node, and not just the searching node
			saveNode = &ar[i];
			break;
		}
	}
	//if we didn't find a close one and the close one is just this one, return a node out of bounds - other methods will interpret this as invalid 
	if (saveNode->shape.getPosition() == prim.shape.getPosition()) 
		return placeholder;
	//otherwise, return the valid, close node
	else
		return *saveNode;
}

void ConflictMode::mutate(Person& person)
{
	int random = 1 + (rand() % 1000);

	//mutation 1: get healthier
	if (random == 500)
	{
		person.updateHealth(person.radius + 1);
	}
	//mutation 2: get stronger
	if (random == 501) {
		person.damage += 1;
	}

	//mutation 3: get faster
	if (random == 502) {
		person.upSpeed += .05;
		person.downSpeed += .05;
		person.leftSpeed += .05;
		person.rightSpeed += .05;
	}

	//mutation 4: if diseased, SUFFER
	if (random % 100 == 0) {
		person.sufferDiseaseEffects();
	}
}

//function the decide of a spawner of another color is close
bool ConflictMode::otherSpawnerClose(Person& prim)
{
	int x = prim.shape.getPosition().x;
	int y = prim.shape.getPosition().y;
	for (unsigned i = 0; i < spawners.size(); i++) {
		//if both the x and y coordinates of the spawner are within a distance of 100 from the x and y coordinates of prim, the spawner is close
		if (abs(spawners[i].getPosition().x - x) < 100 && abs(spawners[i].getPosition().y - y) < 100 && spawners[i].getFillColor() != prim.myCol.color) {
			return true;
		}
	}
	return false;
}

bool ConflictMode::otherSpawnerSomewhatClose(Person& prim)
{
	int x = prim.shape.getPosition().x;
	int y = prim.shape.getPosition().y;
	for (unsigned i = 0; i < spawners.size(); i++) {
		//if the x and y are within 2000, the spawner is relatively close
		if (abs(spawners[i].getPosition().x - x) < 2000 && abs(spawners[i].getPosition().y - y) < 2000 && spawners[i].getFillColor() != prim.myCol.color) {
			return true;
		}
	}
	return false;
}

void ConflictMode::checkIfColonyIsAlive()
{
	
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

	//if the colony's spawner could not be found, the colony itself was declared to be dead, and the death message hasn't been displayed,
	//show the death message, remember that it has been showed for this colony, then set the colony's array index to 0 (to indicate death)
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
}

void ConflictMode::moveNode(Person& prim, Person& closest)
{
	//if a node has been found or not 
	bool found = false;

	//distance from the close node 
	float dist = prim.distance(closest);

	//if the closest node isn't the same node, isn't extremely far away, and it has a different color, move towards it
	if (dist != 0 && dist < 1000 && prim.myCol.color != closest.myCol.color) {
		found = true;
		moveTowardNode(prim, closest);
	}

	//if there's still spawners and they're somewhat close, and we couldn't find anyone who matches the above description, find the spawner
	else if (spawners.size() > 0 && otherSpawnerSomewhatClose(prim)) { 
		findSpawner(prim);
		found = true;
	}

	//if the only spawner on board doesn't match this person's color, find their spawner
	else if (spawners.size() == 1 && spawners[0].getFillColor() != prim.myCol.color) { 
		findSpawner(prim); 
	}

	//if the only spawner on board matches this person's color, find a close node, a return a bool value for if a close one was found
	else if (spawners.size() == 1 && spawners[0].getFillColor() == prim.myCol.color) {
		found = findHardClose(prim);
	}

	//if no spawners are on the board and none of the above worked, no one was found  
	else if (spawners.size() == 0) {
		found = false;
	}

	//if no one was found, go to the center 
	if (!found) { 
		prim.moveToCenter();

	}
}

void ConflictMode::fillAr(int x, int y, Colony col)
{
	Person p(x, y, col, map.m);
	//if the person spawned is an animal, give them some beefy stats 
	if (p.myCol.color == sf::Color::White) {
		p.damage = 10;
		p.updateHealth(60);
		p.defaultSpeed = .5; 
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
	//don't allow more than 80 people on the board at once 
	if (allPlaced && ar.size() <= 80) {
		for (unsigned i = 0; i < spawners.size(); i++) {
			Colony curCol(spawners[i].getFillColor());

			//number to change the spawn rate based on the size of the spawner
			const int num = (1.0 / (2.0 * spawners[i].getSize().x)) * 10000;

			int random = 1 + (rand() % num); 
			int random2 = 1 + (rand() % num);

			//if luck is in our favor, spawn someone 
			if (random == 1 && random2 == 2) {
				fillAr(spawners[i].getPosition().x, spawners[i].getPosition().y, curCol);
			}
		}
	}
}

void ConflictMode::findSpawner(Person& prim)
{
	//index of the close spawner - currently invalid
	int closest = 5;

	//distance from the spawner - currently something way too big 
	float dist = 10000;

	//find the spawner with the lowest dist, then save its index
	for (unsigned i = 0; i < spawners.size(); i++) {
		float dx = spawners[i].getPosition().x - prim.position.x;
		float dy = spawners[i].getPosition().y - prim.position.y;
		float curDist = sqrt(dx * dx + dy * dy);
		if (curDist < dist && spawners[i].getFillColor() != prim.myCol.color) {
			dist = curDist;
			closest = i;
		}
	}

	//if we found a valid spawner, move towards it 
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
			//if they intersect, make the spawner take damage 
			if (prim.shape.getGlobalBounds().intersects(spawners[closest].getGlobalBounds()) && spawners[closest].getFillColor() != prim.myCol.color) {
				curScale.x = curScale.x - prim.damage;
				curScale.y = curScale.y - prim.damage;
				spawners[closest].setSize(curScale);
			}
			i++;
		}
	}

}

void ConflictMode::updateNodes(sf::RenderWindow& window, sf::Time& elapsed_time)
{
	//flags that check on every time this function is called if each colony is still alive 
	bool redCurAlive = false;
	bool greenCurAlive = false;
	bool blueCurAlive = false;
	bool yellowCurAlive = false;
	if (!ar.empty()) {
		for (auto& i : ar)
		{
			//check if at least one person from a given colony is alive - if not found when looping through the entire array, the whole colony must be gone
			if (i.myCol.color == sf::Color::Red)
				redCurAlive = true;
			else if (i.myCol.color == sf::Color::Green)
				greenCurAlive = true;
			else if (i.myCol.color == sf::Color::Blue)
				blueCurAlive = true;
			else if (i.myCol.color == sf::Color::Yellow)
				yellowCurAlive = true;

			if (elapsed_time.asMilliseconds() % 100 == 0) {
				//if another spawner is very close, go directly to it and do nothing else 
				if (otherSpawnerClose(i)) {
					findSpawner(i);
				}

				else {
					Person* p = &findClose(i); 
					//random chance to generate a disease
					if (i.generateDisease())
						updateStatusBar(bar, i.name + " from " + i.myCol.to_string() + " Colony generated a disease!");
					//random chance to recover from disease (if they are diseased) 
					else if (i.recoverFromDisease())
						updateStatusBar(bar, i.name + " from " + i.myCol.to_string() + " Colony has recovered!");
					//chance for mutation, then move to close node and close spawner, chance to spawn animal  
					mutate(i);	
					moveNode(i, *p); 
					findSpawner(i);
					spawnAnimal();
				}
			}
			move(i);
			window.draw(i.shape);
		}
		//save the local values into the global ones 
		redColAlive = redCurAlive;
		greenColAlive = greenCurAlive;
		blueColAlive = blueCurAlive;
		yellowColAlive = yellowCurAlive;
		checkIfColonyIsAlive();

		//check for a victory and decide weather conditions each second 
		if (elapsed_time.asMilliseconds() % 1000 == 0) {
			checkForVictory(window);
			decideWeatherEffects(); 
		}
		//every 30 seconds, reset the weather effects 
		if (elapsed_time.asMilliseconds() % 30000 == 0 && weatherEffectsActive) {
			resetWeatherEffects();
		}
	}
}

void ConflictMode::updateSpawners(sf::RenderWindow& window)
{
	int spawnerSize = spawners.size();
	for (int i = 0; i < spawnerSize; i++) {
		spawn();
		//take it off the screen if it's size is 0 or less
		if (spawners[i].getSize().x <= 0 && spawners[i].getSize().y <= 0) {
			removeSpawner(i);
			spawnerSize = spawners.size();
		}
		else
			window.draw(spawners[i]);
	}
}

bool ConflictMode::detectExitClick(ExitButton button)
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
	int random = 1 + (rand() % 5000000); 
	if (random == 1) {
		int randomX = 1 + (rand() % 1250); 
		int randomY = 1 + (rand() % 690);
		fillAr(randomX, randomY, _otherCol);
		updateStatusBar(bar, "An Vicious Animal Has Spawned!");
	}
}

void ConflictMode::decideWeatherEffects()
{
	if (!weatherEffectsActive) {
		int random = 1 + (rand() % 100);
		switch (random) {
		case 1:
			weather = Updraft;
			break;
		case 2:
			weather = Downdraft;
			break;
		case 3:
			weather = Leftdraft;
			break;
		case 4:
			weather = Rightdraft;
			break;
		default:
			weather = NoWeather;
			break;
		}
		//once decided, set the weather effects 
		setWeatherEffects();
	}
}

void ConflictMode::setWeatherEffects()
{
	//for each person on the screen, if  their weather effect flag hasn't been set, change their speed accordingly, and then set their weather effects flag to true
	//then update the global flag for the weather effects and put a message on the screen
	switch (weather) {
	case Updraft:
		for (int i = 0; i < ar.size(); i++) {
			if (!ar[i].weatherEffectsSet) {
				ar[i].upSpeed += .02f; 
				ar[i].weatherEffectsSet = true;
			}
		}
		
		weatherEffectsActive = true;
		updateStatusBar(bar, "An upwards breeze hit the nodes!");
		break;
	case Downdraft:
		for (int i = 0; i < ar.size(); i++) {
			if (!ar[i].weatherEffectsSet) {
				ar[i].downSpeed += .02f;
				ar[i].weatherEffectsSet = true;
			}
		}
		weatherEffectsActive = true;
		updateStatusBar(bar, "A downwards breeze has hit the nodes!");
		break;
	case Leftdraft:
		for (int i = 0; i < ar.size(); i++) {
			if (!ar[i].weatherEffectsSet) {
				ar[i].leftSpeed += .02f;
				ar[i].weatherEffectsSet = true;
			}
		}
		weatherEffectsActive = true;
		updateStatusBar(bar, "A leftwards breeze has hit the nodes!");
		break;
	case Rightdraft:
		for (int i = 0; i < ar.size(); i++) {
			if (!ar[i].weatherEffectsSet) {
				ar[i].rightSpeed += .02f;
				ar[i].weatherEffectsSet = true;
			}
		}
		weatherEffectsActive = true;
		updateStatusBar(bar, "A rightwards breeze has hit the nodes!");
		break;
	case NoWeather:
		break;
	default: 
		break;
	}
}

void ConflictMode::resetWeatherEffects()
{
	for (int i = 0; i < ar.size(); i++) {
		ar[i].resetSpeed();
	}
	weatherEffectsActive = false;
	updateStatusBar(bar, "The breeze has subsided");
}

void ConflictMode::checkForVictory(sf::RenderWindow& window)
{
	int numAlive = 0;
	for (int i = 0; i < sizeof(aliveCols) / sizeof(aliveCols[0]); i++) {
		if (aliveCols[i] == 1) {
			numAlive++;
		}
		//no need to check the rest if more than 1 is alive 
		if (numAlive > 1)
			break;
	}
	if (numAlive == 1 || numAlive == 0) {
		gameOver = true;
	}
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

string ConflictMode::declareWinner()
{
	bool aliveColFound = false;
	int i = 0;
	//something invalid
	int aliveIndex = -1;
	//find out which colony is alive - should be either 1 or 0, depending if the colonies all kill each other or not 
	while (i < 4 && !aliveColFound) {
		if (aliveCols[i] == 1) {
			aliveColFound = true;
			aliveIndex = i;
		}
		i++;
	}
	if (aliveColFound) {
		switch (aliveIndex) {
		case 0:
			return "Red Colony has Won!";
		case 1:
			return "Green Colony has Won!";
		case 2:
			return "Blue Colony has Won!";
		case 3:
			return "Yellow Colony has Won!";
		defualt:
			throw std::invalid_argument("Houston, we got a problem");
		}
	}
	//if we did not go through the if statement, that means that 0s were found at all indexes, thus the colonies all killed each other and there were no survivors, so return something else
	return "Everyone annihilated each other...\nThere is no winner.";
}

void ConflictMode::playGame()
{
	//start the clock
	sf::Clock r;
	sf::Time elapsed_time;

	//load the map texture
	sf::Texture maptext;
	maptext.loadFromFile(map.to_string());
	sf::Sprite map(maptext);

	//game loop
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

		//pre-game spawner placement logic
		if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && !allPlaced)
			setSpawnPoints();
		if (spawners.size() == 4) {
			if (!allPlaced) 
				updateStatusBar(bar, "Let the simulation begin!");
			allPlaced = true;
		}

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
		text.setString(declareWinner()); 
		text.setPosition(600, 300); //this is off center, fix this 
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