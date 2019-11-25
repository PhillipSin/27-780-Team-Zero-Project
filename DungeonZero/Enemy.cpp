#include <fstream>
#include <iostream>
#include <string>
#include <queue>
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

//1 forward, 2 left, 3 right, 4 back
void Enemy::move(int d, Maze& aMaze) {
	if (d == 1 && yPos > 0 && aMaze.getMap(xPos,yPos-1)!= "1") {
		yPos=yPos-1;
	}
	else if (d == 2 && yPos > 0 && aMaze.getMap(xPos-1,yPos)!= "1") {
		xPos= xPos-1;
	}
	else if (d == 3 && xPos < MAP_SIZE - 1 && aMaze.getMap(xPos+1,yPos) != "1") {
		xPos++;
	}
	else if (d == 4 && yPos < MAP_SIZE - 1 && aMaze.getMap(xPos,yPos+1) != "1") {
		yPos++;
	}
	else {
		cout << "What are you doing? You can't move there." << endl;
	}
}

void Enemy::attack(Entity& anEntity) {
	//allow it to reference player
	anEntity.loseHp(ATTACK_POWER);

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

void Enemy::findBestPath(Entity& anEntity, Maze& aMaze)
{
	// these will help me check the four surrounding squares
	int rowAdjust[4] = { -1, 0, 1, 0 };
	int colAdjust[4] = { 0, 1, 0, -1 };

	// create a queue to hold the nodes to process
	struct node { int row, col, distance; };
	queue<node> processQueue;

	// create a "visited node" array and mark each obstacle as visited
	bool visited[MAX_MAP_SIZE][MAX_MAP_SIZE];
	for (int i = 0; i < MAX_MAP_SIZE; i++)
		for (int j = 0; j < MAX_MAP_SIZE; j++)
			visited[i][j] = true;

	// create a parent array (to be able to reconstruct shortest path)
	int parent[MAX_MAP_SIZE][MAX_MAP_SIZE];

	// set all obstacles to visited and nagivable to not visited
	// set all parent values to -1
	for (int i = 1; i <= aMaze.getRow(); i++)
		for (int j = 1; j <= aMaze.getCol(); j++) {
			if (aMaze.getMap(i, j) == "0")
				visited[i][j] = false;
			parent[i][j] = -1;
		}

	// set the start of the path as the location of the entity
	node startNode = { xPos, yPos, 0 };
	processQueue.push(startNode);
	visited[startNode.row][startNode.col] = true;

	bool foundEnd = false;
	int testRow, testCol;

	node current;

	// do breadth-first search
	while (!foundEnd && !processQueue.empty()) {
		current = processQueue.front();
		processQueue.pop();

		// check if end is found
		if (current.row == anEntity.getY() && current.col == anEntity.getX()) {
			setShortestPath(parent, aMaze);
			foundEnd = true;
		}
		else {
			// visit four possible child nodes and add to queue if appropriate
			for (int i = 0; i < 4; i++) {
				testRow = current.row + rowAdjust[i];
				testCol = current.col + colAdjust[i];
				if (moveAllowed(testRow, testCol, aMaze) && !visited[testRow][testCol]) {
					node newNode = { testRow, testCol, current.distance + 1 };
					processQueue.push(newNode);
					visited[testRow][testCol] = true;
					parent[testRow][testCol] = current.row * MAX_MAP_SIZE + current.col;
				}
			}
		}
	}

	if (foundEnd)
		cout << "Found a path with " << current.distance << " steps." << endl;
	else
		cout << "No available path to end position." << endl;
}

