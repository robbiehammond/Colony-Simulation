#pragma once
#include "GameMode.h"
class SandboxMode : public GameMode {
public:
	SandboxMode(sf::RenderWindow& _window, sf::Font& _font, Map _map);
	void getUserInput(sf::RenderWindow& window, sf::Event& event);
	void fillAr(int x, int y, Colony col);
	void randomSpawn();
	void moveNode(Person& prim, Person& closest);
	void playGame();
private:
	sf::RenderWindow& window;
	sf::Font& font;
	Map map;
};