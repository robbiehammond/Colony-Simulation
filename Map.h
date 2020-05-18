#pragma once
#include <string>
#include <tuple>
#include <vector>
using namespace std;
typedef tuple<int, int> min_max;

enum MapSelection
{
	Map1,
	Map2,
	Map3
};


class Map
{
public:
	Map( MapSelection _m);
	MapSelection m;
	vector<min_max> x_restrictions;
	vector<min_max> y_restrictions;
private:
	min_max x_restriction;
	min_max y_restriction;
	void setRestrictions();
};
