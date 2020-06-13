#pragma once
#include "Person.h"
#include "Colony.h"

enum Mode {
	Sandbox,
	Conflict,
	About,
	None,
};

struct StatusBar {
	StatusBar(sf::RenderWindow& _window, sf::Font& _font);
	sf::RectangleShape outline;
	sf::RenderWindow& window;
	sf::Font& font;
	sf::Text displayedText;
};

struct exitButton {
	exitButton(sf::RenderWindow& _window, sf::Font& _font);
	sf::RectangleShape outline;
	sf::RenderWindow& window;
	sf::Font& font;
	sf::Text closeText;

};

//abstract class that holds stuff that all game modes share goes here
class GameMode {
public:
	string sfColorToString(sf::Color color);
	vector<Person> ar;
	void move(Person& p);
	//TODO - make findClose to be virtual Person& findClose(Person& prim) and then use the same code from conflict mode. This really shouldn't affect SandboxMode much besides having to make certain things a pointer, but nothing else should be different
	virtual Person& findClose(Person& prim) = 0;
	bool findHardClose(Person& prim);
	virtual void mutate(Person& person) = 0;
	void drawStatusBar(StatusBar& s);
	void updateStatusBar(StatusBar& bar, string s);
	void drawExitButton(exitButton& button);
	void moveTowardNode(Person& prim, Person& closest); //could go to person class, maybe do that at anotehr point
	virtual void getUserInput(sf::RenderWindow& window, sf::Event& event) = 0; //controls are slightly different for each mode
	virtual void updateNodes(sf::RenderWindow& window, sf::Time& elapsed_time) = 0;
	virtual void removeAndShuffle(sf::Time& elapsed_time) = 0;
	virtual void playGame() = 0;
	virtual void moveNode(Person& prim, Person& closest) = 0;
};