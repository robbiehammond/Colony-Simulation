#pragma once
#include "GameMode.h"

enum Weather {
	Updraft,
	Downdraft,
	Leftdraft,
	Rightdraft,
	NoWeather
};

class ConflictMode : public GameMode {
public:
	ConflictMode(sf::RenderWindow& _window, sf::Font& _font, Map _map);
	void fillNameArray();
	void setSpawnPoints();
	Person& findClose(Person& prim);
	Person& findVeryClose(Person& prim);
	void mutate(Person& person);
	bool otherSpawnerClose(Person& prim);
	bool otherSpawnerSomewhatClose(Person& prim);
	void checkIfColonyIsAlive();
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
	void spawnAnimal();
	void decideWeatherEffects();
	void setWeatherEffects();
	void resetWeatherEffects();
	void checkForVictory(sf::RenderWindow& window);
	void resetGame();
	string declareWinner();
	void playGame();
private:
	exitButton button;
	StatusBar bar;
	sf::RenderWindow& window;
	sf::Font& font;
	Map map;
};
