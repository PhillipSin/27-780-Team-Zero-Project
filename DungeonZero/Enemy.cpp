#include <fstream>
#include <iostream>
#include <string>
#include "Enemy.h"
#include "maze.h"
#include "entity.h"
#include "fssimplewindow.h"

class Entity;
class Maze;
using namespace std;

//int health;
//int xPos, yPos;
//bool holdingWeapon;
//int dir;

const int MAP_SIZE = 100; //figure out these constants
const int MAX_HP = 20;
const int ATTACK_POWER = 5;

void Enemy::getShort()
{
	for (int i = 1; i <= 15; i++){
		for (int j = 1; j <= 15; j++) {
			cout << shortest[i][j]<<" ";
		}
		cout << endl;
	}
}

//1 forward, 2 left, 3 right, 4 back
void Enemy::move(int x,int y,Maze& aMaze) {
	///*if (d == 1 && yPos > 0 && aMaze.getMap(xPos,yPos-1)!= "1") {
	//	yPos=yPos-1;
	//}
	//else if (d == 2 && yPos > 0 && aMaze.getMap(xPos-1,yPos)!= "1") {
	//	xPos= xPos-1;
	//}
	//else if (d == 3 && xPos < MAP_SIZE - 1 && aMaze.getMap(xPos+1,yPos) != "1") {
	//	xPos++;
	//}
	//else if (d == 4 && yPos < MAP_SIZE - 1 && aMaze.getMap(xPos,yPos+1) != "1") {
	//	yPos++;
	//}*/
	//	// Check Above
	//	if (shortest[yPos + 1][xPos] == true) {
	//		yPos++;
	//	}
	//	// Check Right
	//	else if (shortest[yPos][xPos + 1] == true) {
	//		xPos++;
	//	}
	//	// Check Below
	//	else if (shortest[yPos - 1][xPos] == true) {
	//		yPos--;
	//	}
	//	// Check Left
	//	else if (shortest[yPos][xPos - 1] == true) {
	//		xPos--;
	//	}
	aMaze.edit(xPos, yPos, steppingOn);
	steppingOn = aMaze.getMap(x, y);
	xPos = x;
	yPos = y;
	aMaze.edit(xPos, yPos, "e");

}

void Enemy::drawShortest()
{
		if (calculatedShortest) {
			// draw shortest path (diamonds)
			for (int i = 1; i < MAX_MAP_SIZE; i++) {
				for (int j = 1; j < MAX_MAP_SIZE; j++) {
					cout << shortest[i][j] << " ";
				}
				cout << endl;
			}
	}
}

bool Enemy::attack(Entity& anEntity) {
	//allow it to reference player
	int pxPos = anEntity.getX();
	int pyPos = anEntity.getY();
	if (living == true) {
		if ((pxPos + 1 == xPos && pyPos == yPos) || (pxPos - 1 == xPos && pyPos == yPos) || (pxPos == xPos && pyPos + 1 == yPos) || (pxPos == xPos && pyPos - 1 == yPos))
		{
			anEntity.loseHp(ATTACK_POWER);
			return true;
		}
	}
	return false;
}

bool Enemy::die(Maze& aMaze)
{
	if (health <= 0) {
		aMaze.replace(xPos, yPos, "0");
		living = false;
		return true;
	}
	return false;
}

bool Enemy::moveAllowed(int row, int col, Maze& aMaze)
{
	// note order of conditions 
	// (I don't check map[row][col] until I am sure that row and col are valid)
	return (row > 0 && row <= aMaze.getRow()
		&& col > 0 && col <= aMaze.getCol()
		&& aMaze.getMap(row, col) == "0");
}



void Enemy::setShortestPath(int parentArray[MAX_MAP_SIZE][MAX_MAP_SIZE], Maze& aMaze)
{
	int rowSize = aMaze.getRow();
	int colSize = aMaze.getCol();
	int currRow, currCol;

	// clear shortest array
	for (int i = 1; i < MAX_MAP_SIZE; i++)
		for (int j = 1; j < MAX_MAP_SIZE; j++)
			shortest[i][j] = false;

	// follow parent array backwards from maze end
	// marking as true all squares that are in path
	currRow = aMaze.getEndY();
	currCol = aMaze.getEndX();

	int temp1 = parentArray[0][0];
	int nextParent = parentArray[currRow][currCol];
	while (nextParent != -1) {
		shortest[currRow][currCol] = true;
		currRow = nextParent / MAX_MAP_SIZE;
		currCol = nextParent % MAX_MAP_SIZE;
		nextParent = parentArray[currRow][currCol];
	}

	calculatedShortest = true;
}


void Enemy::setShortestPath(int parentArray[MAX_MAP_SIZE][MAX_MAP_SIZE], Maze& aMaze, Entity& anEntity)
{
	int rowSize = aMaze.getRow();
	int colSize = aMaze.getCol();
	int currRow, currCol;

	// clear shortest array
	for (int i = 1; i < MAX_MAP_SIZE; i++)
		for (int j = 1; j < MAX_MAP_SIZE; j++)
			shortest[i][j] = false;

	// follow parent array backwards from maze end
	// marking as true all squares that are in path
	currRow = anEntity.getY();
	currCol = anEntity.getX();

	int temp1 = parentArray[6][7];
	int nextParent = parentArray[currRow][currCol];
	while (nextParent != -1) {
		shortest[currRow][currCol] = true;
		currRow = nextParent / MAX_MAP_SIZE;
		currCol = nextParent % MAX_MAP_SIZE;
		nextParent = parentArray[currRow][currCol];
	}

	calculatedShortest = true;
}

