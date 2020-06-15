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

	//fills the name array from the name file 
	void fillNameArray();

	//put the spawners down before the game starts 
	void setSpawnPoints();

	//find any person that is relatively close
	Person& findClose(Person& prim);

	//function to decide which mutation, if any, should occur on this iteration of the game loop
	void mutate(Person& person);

	//function the decide of a spawner of another color is close
	bool otherSpawnerClose(Person& prim);

	//decides if we're anywhere near a spawner of a different color
	bool otherSpawnerSomewhatClose(Person& prim);

	//function that runs through the vector of of spawners, checking the colony still exists, then checks the other flags for the existence of the colony
	void checkIfColonyIsAlive();

	//convert the user's clicks to events on the screen
	void getUserInput(sf::RenderWindow& window, sf::Event& event);

	//algorithm controlling most of what happens on the screen
	void updateNodes(sf::RenderWindow& window, sf::Time& elapsed_time);

	//logic to update spawner conditions for each spawner each time this function is called 
	void updateSpawners(sf::RenderWindow& window);

	//algorithm controlling most of the movement on the screen
	void moveNode(Person& prim, Person& closest);

	//function to put new people on the board 
	void fillAr(int x, int y, Colony col);

	//logic to have the spawners actually spawn people 
	void spawn();

	//finds the closest spawner that isn't our own color
	void findSpawner(Person& prim);

	//function to check if the exit button has been clicked
	bool detectExitClick(ExitButton button);

	//function to remove dead spawners from the array and put out the message that they have been destroyed 
	void removeSpawner(int spawnerIndex);

	//function to randomly decide if an animal should be spawned
	void spawnAnimal();

	//function to randomly dictate the weather going on in the game 
	void decideWeatherEffects();

	//function to set the weather effects decided
	void setWeatherEffects();

	//removes any active weather effects
	void resetWeatherEffects();

	//loop through the colony array - if only one number or no number is 1, declare that the game has ended
	void checkForVictory(sf::RenderWindow& window);

	//wipe the effects of last game and reset everything back to default 
	void resetGame();

	//declare which colony (if any) has won
	string declareWinner();

	//main game function 
	void playGame();

private:
	ExitButton button;
	StatusBar bar;
	sf::RenderWindow& window;
	sf::Font& font;
	Map map;
};
