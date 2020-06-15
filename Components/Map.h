#pragma once
#include <map>
#include <string>
#include <tuple>
#include <vector>
using namespace std;
typedef tuple<int, int> min_max;

enum MapSelection
{
	Map0, //empty map, essentially sandbox mode
	Map1,
	Map2,
	Map3
};


class Map
{
public:
	Map( MapSelection _m);

	//used essentially to get the name of the file that contains the map image 
	string to_string();

	//pushes one set of restricted coordinates back into the x and y restrictions vector
	void push_back(int startX, int endX, int startY, int endY);

	//the collection of string maps in string form
	map<MapSelection, string> stringMapNames;

	//the selected map 
	MapSelection m;

	//the lower and upper bounds of a restricted area 
	vector<min_max> x_restrictions;
	vector<min_max> y_restrictions;
private:

	min_max x_restriction;
	min_max y_restriction;

	//puts boundaries on the edges of the screen
	void setScreenBoundaries();

	//set other restrictions on the map 
	void setRestrictions();
};
