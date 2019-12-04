#pragma once
#include "Maze.h"
#include "Enemy.h"
class Maze;
class Enemy;

class Entity
{
private:
	int xPos, yPos;
	int direction;
	int health;
	int attackNum;
	bool holdingWeapon;
	int damage;
	bool holdingKey;
	int holdingPotion;
public:
	Entity(int xLoc, int yLoc, int dir)
	{
		xPos = xLoc;
		yPos = yLoc;
		holdingKey = 0;
		direction = dir;
		attackNum = 1;
		health = 100;
		holdingPotion = 0;
		holdingWeapon = 0;
		damage = 1;
	}
	void draw();
	int getHealth() { return health; };
	void setDirection(int dir);
	bool checkBelow(Maze& aMaze);
	void setKey() { holdingKey = false; };
	bool moveUp(Maze& aMaze);
	bool hasKey() { return holdingKey; };
	bool moveDown(Maze& aMaze);
	void changePos(int x, int y) { xPos = x; yPos = y; };
	bool moveLeft(Maze& aMaze);
	bool moveRight(Maze& aMaze);
	bool reachedGoal(Maze& aMaze);
	bool openDoor(Maze& aMaze);
	bool checkEnemyInFront(Enemy& aEnemy);
	int getX() { return xPos; };
	int getY() { return yPos; };
	int getDirection() { return direction; };
	void changeDirection(bool dir);
	int getNumPotions() { return holdingPotion; }
	bool attack(int x, int y, Maze& aMaze, Enemy& anEnemy);
	bool drink();
	int pickUp(int x, int y, Maze& aMaze);
	void loseHp(int x);
};

