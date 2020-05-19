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

void Map::setRestrictions()
{

	//before switch, put bounds that are the same for every map (ie edge boundaries)
	
	switch (m) {
	case Map1:
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
		break;
	case Map3:
		break;
	default:
		std::cout << "We got problems" << endl;
	}
}

string Map::to_string()
{
	cout << stringMapNames.at(m);
	return stringMapNames.at(m);
}