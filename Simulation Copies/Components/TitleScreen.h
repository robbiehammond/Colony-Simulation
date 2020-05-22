#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
using namespace std;

class TitleScreen {
public:
	TitleScreen(sf::RenderWindow _window, sf::Font _font);
	void createMapBoxes(unsigned int x, unsigned int y, string imgName); //might need another field for image path later, or just get rid of the space later on
private:


};