
#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include "fssimplewindow.h"

const int MAX_MAP_SIZE = 100;

using namespace std;
class Maze;
class Entity;

class Enemy {
private:
	int health;
	int xPos, yPos;
	bool calculatedShortest;
	bool adjacentPlayer;
	int parentArray[MAX_MAP_SIZE][MAX_MAP_SIZE];
	bool shortest[MAX_MAP_SIZE][MAX_MAP_SIZE];

	//array pathToUser;

public:
	Enemy(int xLoc, int yLoc)
	{
		xPos = xLoc;
		yPos = yLoc;
	}
	void detectAdjacentPlayer();
	void move();
	void attack(Entity& anEntity);
	bool moveAllowed(int row, int col, Maze& aMaze);
	void setShortestPath(int parentArray[MAX_MAP_SIZE][MAX_MAP_SIZE], Maze& aMaze);
	void findBestPath(Entity& anEntity, Maze& aMaze);
	//this function needs the x,y position of the player entity and build it onto the pathToUser array
};