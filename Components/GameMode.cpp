#include "GameMode.h"
#include <iostream>

void GameMode::move(Person& p)
{
	int random = 1 + (rand() % 4);
	switch (random) {
	case 1:
		p.moveUp();
		break;
	case 2:
		p.moveDown();
		break;
	case 3:
		p.moveLeft();
		break;
	case 4:
		p.moveRight();
		break;
	}
}

Person GameMode::findClose(Person& prim)
{
	Person placeholder(-10000, -100000, prim.myCol, prim.curMap);
	
	float curMinDist = 400;

	Person* saveNode = &prim;

	for (auto i = 0; i < ar.size(); i++) {
		const float curNodeDist = prim.distance(ar[i]);
		if (curNodeDist < curMinDist && curNodeDist != 0 && ar[i].myCol.color != prim.myCol.color) {
			saveNode = &ar[i];
			break;
		}
	}
	if (saveNode->shape.getPosition() == prim.shape.getPosition()) {
		return placeholder;
	}
	else
		return *saveNode;
}

bool GameMode::findHardClose(Person& prim)
{

	Person placeholder(-10000, -100000, prim.myCol, prim.curMap);

	float curMinDist = 400;

	Person* saveNode = &prim;

	for (auto i = 0; i < ar.size(); i++) {
		const float curNodeDist = prim.distance(ar[i]);
		if (curNodeDist < curMinDist && curNodeDist != 0 && ar[i].myCol.color != prim.myCol.color) {
			saveNode = &ar[i];
			break;
		}
	}
	if (saveNode->shape.getPosition() == prim.shape.getPosition()) {
		return false;
	}
	else {
		Person closest = *saveNode;
		int dist = prim.distance(closest);
		if (dist != 0 && dist < 1000 && prim.myCol.color != closest.myCol.color) {
			int i = 0;
			while (i < 3) {
				float dx = closest.position.x - prim.position.x;
				float dy = closest.position.y - prim.position.y;
				if (dx > 0)
					prim.moveRight();
				if (dx < 0)
					prim.moveLeft();
				if (dy > 0)
					prim.moveDown();
				if (dy < 0)
					prim.moveUp();
				if (prim.shape.getGlobalBounds().intersects(closest.shape.getGlobalBounds()) && closest.shape.getPosition() != prim.shape.getPosition()) {
					prim.updateHealth(prim.health - closest.damage);
					if (prim.damage > 1)
						prim.damage -= 1;
					closest.updateHealth(closest.health - 1);
				}
				i++;
			}
		}
	}
	return true;
}


void GameMode::mutate(Person& person)
{
	int random = 1 + (rand() % 1000);
	//mutation 1: get healthier
	if (random == 500)
	{
		person.updateHealth(person.radius + 1);
	}
	//mutation 2: get stronger
	if (random == 501) {
		person.damage += 1;
	}
}
