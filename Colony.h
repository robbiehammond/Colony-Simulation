#pragma once
#include <vector>
#include "Person.h"
//Divide Colonies by Color, include in constructor later

using namespace std;

class Colony
{
public:
	Colony();
	void movePeople();
	void fillArr(int x_cord, int y_cord);
	void findClosest(Person& p);
};
