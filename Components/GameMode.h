#pragma once
#include "Person.h"
#include "Colony.h"

enum Mode {
	Sandbox,
	Conflict
};

struct StatusBar {
public:
	StatusBar(int x, int y);
};

//abstract class that holds stuff that all game modes share goes here
class GameMode {
public:
	void move(Person& p);
	Person findClose(Person& prim);
	bool findHardClose(Person& prim);
	void mutate(Person& person);
	virtual void getUserInput(sf::RenderWindow& window, sf::Event& event) = 0; //controls are slightly different for each mode
	virtual void updateNodes(sf::RenderWindow& window, sf::Time& elapsed_time) = 0;
	virtual void removeAndShuffle(sf::Time& elapsed_time) = 0;
	virtual void playGame() = 0;
	virtual void moveNode(Person& prim, Person& closest) = 0;
	vector<Person> ar; 
};