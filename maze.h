#pragma once
#include <string>
#include <vector>
#include "entity.h"
using namespace std;
class Entity;

class Maze
{
private:
	int colSize, rowSize;
	int startX, startY;
	int endX, endY;
	string map[100][100];
	std::string file;
	bool startDef, endDef;
	int obstacleCost = 100000;

public:
	Maze(std::string inFile) { file = inFile; startDef = 1; endDef = 1; }
	void draw();
	bool load();
	vector<vector<string>>view(Entity &anEntity);
	void print();
	void setObstacleCost(int newCost) { obstacleCost = newCost; }
	int getObstacleCost() { return obstacleCost; }
	void save();
	void edit(int locX, int locY);
	string getMap(int i, int j) { return map[i][j]; }
	int getCol() { return colSize; }
	int getRow() { return rowSize; }
	int getStartX() { return startX; }
	int getStartY() { return startY; }
	int getEndX() { return endX; }
	int getEndY() { return endY; }
	void findShortestPath(Entity& anEntity);
};

