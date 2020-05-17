#pragma once
#include "Map.h"


Map::Map(const MapSelection _m)
{
	m = _m;
	setRestrictions();
}

void Map::setRestrictions()
{
	if (m == Map1) {
		x_restriction = make_tuple(100, 200);
		y_restriction = make_tuple(100, 200);
		x_restrictions.push_back(x_restriction);
		y_restrictions.push_back(y_restriction);
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
