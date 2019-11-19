#pragma once
#include "Maze.h"
class Maze;

class Entity
{
private:
	int xPos, yPos;
	int direction;
	int health;
	bool holdingWeapon;
	int holdingPotion;
public:
	Entity(int xLoc, int yLoc, int dir)
	{
		xPos = xLoc;
		yPos = yLoc;
		direction = dir;
		holdingPotion = 0;
		holdingWeapon = 0;
	}
	void draw();
	bool moveUp(Maze& aMaze);
	bool moveDown(Maze& aMaze);
	bool moveLeft(Maze& aMaze);
	bool moveRight(Maze& aMaze);
	bool reachedGoal(Maze& aMaze);
	int getX() { return xPos; };
	int getY() { return yPos; };
	int getDirection() { return direction; };
	void changeDirection(bool dir);
	int getNumPotions() { return holdingPotion; }
	void attack(int x, int y, Maze& aMaze);
	void drink();
	void pickUp(int x, int y, Maze& aMaze);
	void loseHp(int x);
};

