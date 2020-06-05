#pragma once
#include "Person.h"
#include "Colony.h"

enum Mode {
	Sandbox,
	Conflict
};

struct StatusBar {
public:
	StatusBar(sf::RenderWindow& _window, sf::Font& _font);
	sf::RectangleShape outline;
	sf::RenderWindow& window;
	sf::Font& font;
	sf::Text displayedText;
	
};

//abstract class that holds stuff that all game modes share goes here
class GameMode {
public:
	vector<Person> ar;
	void move(Person& p);
	virtual Person findClose(Person& prim) = 0;
	bool findHardClose(Person& prim);
	void mutate(Person& person);
	void drawStatusBar(StatusBar& s);
	void updateStatusBar(StatusBar& bar, string s); //might want to put this into the StatusBar struct at some point, also the string must be under or equal to 41 characters
	virtual void getUserInput(sf::RenderWindow& window, sf::Event& event) = 0; //controls are slightly different for each mode
	virtual void updateNodes(sf::RenderWindow& window, sf::Time& elapsed_time) = 0;
	virtual void removeAndShuffle(sf::Time& elapsed_time) = 0;
	virtual void playGame() = 0;
	virtual void moveNode(Person& prim, Person& closest) = 0;
};