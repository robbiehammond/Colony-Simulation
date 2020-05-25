#pragma once
#include "Person.h"
#include "Colony.h"

enum Mode {
	Sandbox,
	Conflict
};
//abstract class that holds stuff that all game modes share goes here
class GameMode {
public:
	void move(Person& p);
	Person findClose(Person& prim);
	void moveNode(Person& prim, Person& closest);
	void mutate(Person& person);
	virtual void getUserInput(sf::RenderWindow& window, sf::Event& event) = 0; //controls are slightly different for each mode
	virtual void playGame() = 0;
	vector<Person> ar;
private:

};