#pragma once
#include "Map.h"

#include <iostream>


Map::Map(const MapSelection _m)
{
	m = _m;
	stringMapNames.insert(std::pair<MapSelection, string>(Map0, "Map0.png"));
	stringMapNames.insert(std::pair<MapSelection, string>(Map1, "Map1.png"));
	stringMapNames.insert(std::pair<MapSelection, string>(Map2, "Map2.png"));
	stringMapNames.insert(std::pair<MapSelection, string>(Map3, "Map3.png"));
	setRestrictions();
}

//puts boundaries on the edges of the screen
void Map::setScreenBoundaries()
{
	//left edge boundary
	x_restriction = make_tuple(-3000, 0);
	y_restriction = make_tuple(-3000, 3000);
	x_restrictions.push_back(x_restriction);
	y_restrictions.push_back(y_restriction);

	//right edge boundary
	x_restriction = make_tuple(1280, 3000);
	y_restriction = make_tuple(-3000, 3000);
	x_restrictions.push_back(x_restriction);
	y_restrictions.push_back(y_restriction);


	//top boundary
	x_restriction = make_tuple(-3000, 3000);
	y_restriction = make_tuple(720, 3000);
	x_restrictions.push_back(x_restriction);
	y_restrictions.push_back(y_restriction);

	//bottom boundary
	x_restriction = make_tuple(-3000, 3000);
	y_restriction = make_tuple(-3000, 0);
	x_restrictions.push_back(x_restriction);
	y_restrictions.push_back(y_restriction);
}

void Map::setRestrictions()
{

	//before switch, put bounds that are the same for every map (ie edge boundaries)
	
	switch (m) {
	case Map0:
		setScreenBoundaries();
		break;

	case Map1:
		setScreenBoundaries();
		//top left square
		x_restriction = make_tuple(100, 200);
		y_restriction = make_tuple(100, 200);
		x_restrictions.push_back(x_restriction);
		y_restrictions.push_back(y_restriction);

		//top right square
		x_restriction = make_tuple(1060, 1160);
		y_restriction = make_tuple(100, 200);
		x_restrictions.push_back(x_restriction);
		y_restrictions.push_back(y_restriction);

		//bottom left square
		x_restriction = make_tuple(100, 200);
		y_restriction = make_tuple(520, 620);
		x_restrictions.push_back(x_restriction);
		y_restrictions.push_back(y_restriction);

		//bottom rigt square
		x_restriction = make_tuple(1060, 1160);
		y_restriction = make_tuple(520, 620);
		x_restrictions.push_back(x_restriction);
		y_restrictions.push_back(y_restriction);

		break;
	case Map2:
		setScreenBoundaries();
		//top left
		x_restriction = make_tuple(480, 580);
		y_restriction = make_tuple(200, 300);
		x_restrictions.push_back(x_restriction);
		y_restrictions.push_back(y_restriction);

		//top right 
		x_restriction = make_tuple(660, 760);
		y_restriction = make_tuple(200, 300);
		x_restrictions.push_back(x_restriction);
		y_restrictions.push_back(y_restriction);

		//bottom left 
		x_restriction = make_tuple(480, 580);
		y_restriction = make_tuple(380, 480);
		x_restrictions.push_back(x_restriction);
		y_restrictions.push_back(y_restriction);

		//bottom right
		x_restriction = make_tuple(660, 760);
		y_restriction = make_tuple(380, 480);
		x_restrictions.push_back(x_restriction);
		y_restrictions.push_back(y_restriction);
		break;
	case Map3:
		setScreenBoundaries();
		//top left
		x_restriction = make_tuple(196, 296);
		y_restriction = make_tuple(120, 220);
		x_restrictions.push_back(x_restriction);
		y_restrictions.push_back(y_restriction);

		//make the rest 
		break;
	default:
		std::cout << "We got problems" << endl;
	}
}

string Map::to_string()
{
	return stringMapNames.at(m);
}