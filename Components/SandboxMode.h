#pragma once
#include "GameMode.h"
class SandboxMode : public GameMode {
public:
	SandboxMode(sf::RenderWindow& _window, sf::Font& _font, Map _map);

	//find a relatively close person
	Person& findClose(Person& prim);

	//mutate to get healthier or stronger
	void mutate(Person& person);

	//convert the user's clicks to events on the screen
	void getUserInput(sf::RenderWindow& window, sf::Event& event);

	//puts people created via click into the vector of people on the screen
	void fillAr(int x, int y, Colony col);

	//move a person to another person, if they're at a valid distance
	void moveNode(Person& prim, Person& closest);

	//algorithm controlling most of what happens on the screen
	void updateNodes(sf::RenderWindow& window, sf::Time& elapsed_time);

	//TODO - move this to GameMode file!
	bool detectExitClick(ExitButton button);

	//main game function 
	void playGame();
private:
	ExitButton button;
	sf::RenderWindow& window;
	sf::Font& font;
	Map map;
};