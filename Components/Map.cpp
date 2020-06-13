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
	//left boundary
	push_back(-3000, 0, -3000, 3000);

	//right boundary
	push_back(1260, 3000, -3000, 3000);

	//top boundary
	push_back(-3000, 3000, 700, 3000);

	//bottom boundary
	push_back(-3000, 3000, -3000, 0);
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
		push_back(100, 200, 100, 200);

		//top right square
		push_back(1060, 1160, 100, 200);

		//bottom left square
		push_back(100, 200, 520, 620);

		//bottom rigt square
		push_back(1060, 1160, 520, 620);
		break;

	case Map2:
		setScreenBoundaries();
		//top left
		push_back(480, 580, 200, 300);

		//top right 
		push_back(660, 760, 200, 300);

		//bottom left 
		push_back(480, 580, 380, 480);

		//bottom right
		push_back(660, 760, 380, 480);
		break;

	case Map3:
		setScreenBoundaries();

		//top left
		push_back(196, 296, 120, 220);

		//top 2nd to left
		push_back(452, 552, 120, 220);

		//top 2nd to right
		push_back(708, 808, 120, 220);

		//top right
		push_back(964, 1064, 120, 220);

		//middle left
		push_back(196, 296, 300, 400);

		//middle right
		push_back(964, 1064, 300, 400);

		//bottom left
		push_back(196, 296, 480, 580);

		//bottom 2nd to left
		push_back(452, 552, 480, 580);

		//bottom 2nd to right
		push_back(708, 808, 480, 580);

		//top right
		push_back(964, 1064, 480, 580);
		break;

	default:
		std::cout << "We got problems" << endl;
	}
}

string Map::to_string()
{
	return stringMapNames.at(m);
}

void Map::push_back(int startX, int endX, int startY, int endY)
{
	min_max Xlimits = make_tuple(startX, endX);
	min_max Ylimits = make_tuple(startY, endY);
	x_restrictions.push_back(Xlimits);
	y_restrictions.push_back(Ylimits);
}
