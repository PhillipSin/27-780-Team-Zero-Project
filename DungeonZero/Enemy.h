#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include "maze.h"
#include "fssimplewindow.h"
const int MAX_MAP_SIZE = 15;
using namespace std;
class Maze;
class Entity;

class Enemy {
private:
	int health;
	bool living;
	string steppingOn;
	//array pathToUser;
	bool calculatedShortest;
	int parentArray[MAX_MAP_SIZE][MAX_MAP_SIZE];
	bool shortest[MAX_MAP_SIZE][MAX_MAP_SIZE];

public:
	int xPos, yPos;
	Enemy(int xLoc, int yLoc)
	{
		steppingOn = "0";
		health = 10;
		xPos = xLoc;
		yPos = yLoc;
		living = true;
	}
	void getShort();
	void setShortestPath(int parentArray[MAX_MAP_SIZE][MAX_MAP_SIZE], Maze& aMaze, Entity& anEntity);
	int getX() { return xPos; };
	int getY() { return yPos; };
	int getHealth() { return health; };
	void damage(int damage) { health -= damage; };
	void move(int x,int y, Maze& aMaze);
	void drawShortest();
	bool attack(Entity& anEntity);
	bool isLiving() { return living; };
	bool die(Maze& aMaze);
	bool moveAllowed(int row, int col, Maze& aMaze);
	void setShortestPath(int parentArray[MAX_MAP_SIZE][MAX_MAP_SIZE], Maze& aMaze);
	void findBestPath(Entity& anEntity, Maze& aMaze);
	//this function needs the x,y position of the player entity and build it onto the pathToUser array
};