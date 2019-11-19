#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include "fssimplewindow.h"

using namespace std;
class Maze;
class Entity;

class Enemy {
private:
	int health;
	int xPos, yPos;
	//array pathToUser;

public:
	Enemy(int xLoc, int yLoc)
	{
		xPos = xLoc;
		yPos = yLoc;
	}
	void move(int d, Maze& aMaze);
	void attack(Entity& anEntity);
	void calcShortestPath(Entity& anEntity);
	//this function needs the x,y position of the player entity and build it onto the pathToUser array
};