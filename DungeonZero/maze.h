#pragma once
#include <string>
#include <vector>
#include "entity.h"
using namespace std;
class Entity;
class Enemy;

class Maze
{
private:
	int colSize, rowSize;
	int startX, startY;
	int endX, endY;
	string map[20][20];
	std::string file;
	bool startDef, endDef;
	int obstacleCost = 100000;

public:
	Maze(std::string inFile) { file = inFile; startDef = 1; endDef = 1; }
	void draw(Entity& anEntity);
	bool load();
	bool moveAllowed(int row, int col);
	vector<vector<string>>view(Entity &anEntity);
	void print();
	void setObstacleCost(int newCost) { obstacleCost = newCost; }
	int getObstacleCost() { return obstacleCost; }
	void save();
	void replace(int i, int j, string thing) { map[i][j] = thing; }
	void edit(int xx, int yy, string val);
	string getMap(int i, int j) { return map[i][j]; }
	int getCol() { return colSize; }
	int getRow() { return rowSize; }
	int getStartX() { return startX; }
	int getStartY() { return startY; }
	int getEndX() { return endX; }
	int getEndY() { return endY; }
	void findShortestPath(Enemy& anEnemy,Entity& anEntity);
};

