#pragma once
#include "GameMode.h"
class ConflictMode : public GameMode {
public:
	ConflictMode(sf::RenderWindow& _window, sf::Font& _font, Map _map);
	void fillNameArray();
	void setSpawnPoints();
	Person findClose(Person& prim);
	bool otherSpawnerClose(Person& prim);
	bool ourSpawnerClose(Person& prim);
	void getUserInput(sf::RenderWindow& window, sf::Event& event);
	void updateNodes(sf::RenderWindow& window, sf::Time& elapsed_time);
	void updateSpawners(sf::RenderWindow& window);
	void moveNode(Person& prim, Person& closest);
	void fillAr(int x, int y, Colony col);
	void spawn();
	void findSpawner(Person& prim);
	void removeAndShuffle(sf::Time& elapsed_time);
	bool detectExitClick(exitButton button);
	void removeSpawner(int spawnerIndex);
	void placePowerUp(sf::RenderWindow& window);
	void playGame();
private:
	exitButton button;
	StatusBar bar;
	sf::RenderWindow& window;
	sf::Font& font;
	Map map;
};
