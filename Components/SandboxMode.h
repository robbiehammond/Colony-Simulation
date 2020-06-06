#pragma once
#include "GameMode.h"
class SandboxMode : public GameMode {
public:
	SandboxMode(sf::RenderWindow& _window, sf::Font& _font, Map _map);
	Person findClose(Person& prim);
	void getUserInput(sf::RenderWindow& window, sf::Event& event);
	void fillAr(int x, int y, Colony col);
	void randomSpawn();
	void moveNode(Person& prim, Person& closest);
	void removeAndShuffle(sf::Time& elapsed_time);
	void updateNodes(sf::RenderWindow& window, sf::Time& elapsed_time);
	bool detectExitClick(exitButton button);
	void playGame();
private:
	exitButton button;
	sf::RenderWindow& window;
	sf::Font& font;
	Map map;
};