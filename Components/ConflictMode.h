#pragma once
#include "GameMode.h"
class ConflictMode : public GameMode {
public:
	ConflictMode(sf::RenderWindow& _window, sf::Font& _font, Map _map);
	void setSpawnPoints();
	bool clickInRange(sf::RectangleShape& object);
	bool spawnerClose(Person& prim);
	void getUserInput(sf::RenderWindow& window, sf::Event& event);
	void updateNodes(sf::RenderWindow& window, sf::Time& elapsed_time);
	void moveNode(Person& prim, Person& closest);
	void fillAr(int x, int y, Colony col);
	void spawn();
	void findSpawner(Person& prim);
	void removeAndShuffle(sf::Time& elapsed_time);
	void checkForDisease(Person& prim);
	void playGame();
private:
	sf::RenderWindow& window;
	sf::Font& font;
	Map map;
};
