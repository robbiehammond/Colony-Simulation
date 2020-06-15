#pragma once
#include "Person.h"
#include "Colony.h"

enum Mode {
	Sandbox,
	Conflict,
	About,
	None,
};

//probably would make the most sense to move this to conflict mode, since it doesn't appear at all in sandbox mode
struct StatusBar {
	StatusBar(sf::RenderWindow& _window, sf::Font& _font);
	sf::RectangleShape outline;
	sf::RenderWindow& window;
	sf::Font& font;
	sf::Text displayedText;
};

struct ExitButton {
	ExitButton(sf::RenderWindow& _window, sf::Font& _font);
	sf::RectangleShape outline;
	sf::RenderWindow& window;
	sf::Font& font;
	sf::Text closeText;

};

//abstract class that holds stuff that all game modes share goes here
class GameMode {
public:
	//because SFML has no built in toString function
	string sfColorToString(sf::Color color);

	//randomly move a preson up, down, left, or right
	void move(Person& p);


	//function that returns a value for if a node was found 
	bool findHardClose(Person& prim);

	//MOVE TO CONFLICT WITH THE STATUSBAR STRUCT
	void drawStatusBar(StatusBar& s);
	void updateStatusBar(StatusBar& bar, string s);

	//void detectExitClick(ExitButton button);
	void drawExitButton(ExitButton& button);


	//move one node toward another one 
	void moveTowardNode(Person& prim, Person& closest); //could go to person class, maybe do that at anotehr point

	//removes dead people and shuffles everyone's position in the array, so that the people toward the front of the array don't get unfairly targeted
	void removeAndShuffle(sf::Time& elapsed_time);


	virtual void mutate(Person& person) = 0;
	virtual Person& findClose(Person& prim) = 0;
	virtual void getUserInput(sf::RenderWindow& window, sf::Event& event) = 0; //controls are slightly different for each mode
	virtual void updateNodes(sf::RenderWindow& window, sf::Time& elapsed_time) = 0;
	virtual void playGame() = 0;
	virtual void moveNode(Person& prim, Person& closest) = 0;

	vector<Person> ar;

};