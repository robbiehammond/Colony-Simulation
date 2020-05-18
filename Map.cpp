#pragma once
#include "Map.h"

#include <iostream>


Map::Map(const MapSelection _m)
{
	m = _m;
	setRestrictions();
}

void Map::setRestrictions()
{
	switch (m) {
	case Map1:
		//top left square
		x_restriction = make_tuple(100, 200);
		y_restriction = make_tuple(100, 200);
		x_restrictions.push_back(x_restriction);
		y_restrictions.push_back(y_restriction);

		//top right square
		x_restriction = make_tuple(1080, 1180);
		y_restriction = make_tuple(100, 200);
		x_restrictions.push_back(x_restriction);
		y_restrictions.push_back(y_restriction);

		//bottom left square
		x_restriction = make_tuple(100, 200);
		y_restriction = make_tuple(520, 620);
		x_restrictions.push_back(x_restriction);
		y_restrictions.push_back(y_restriction);

		//bottom rigt square
		x_restriction = make_tuple(1080, 1180);
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
	/*
	switch (m)
	{
	case Map1:
		min_max xRestrict = make_tuple(100, 200);
		min_max yRestrict = make_tuple(100, 200);
		break;
	case Map2:
		break;
	case Map3:
		break;
	default:
		break;
	}
	*/
}
