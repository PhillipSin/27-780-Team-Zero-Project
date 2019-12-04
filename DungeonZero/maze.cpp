#include "Maze.h"
#include "fssimplewindow.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;


struct parentChild {
	vector<int> parent;
	vector<int> child;
};


void drawTarget(int column, int row, string val)
{
	if (val=="1") {
		glColor3ub(0, 0, 0);
	}
	else if (val == "d") {
		glColor3ub(100, 0, 0);
	}

	else {
		glColor3ub(255, 255, 255);
	}

	glBegin(GL_QUADS);
	glVertex2i((row - 1) * 20, (column - 1) * 20);
	glVertex2i((row - 1) * 20, (column) * 20);
	glVertex2i((row) * 20, (column) * 20);
	glVertex2i((row) * 20, (column - 1) * 20);

	glEnd();
	//DrawingUtilNG::drawCube((row-1)*20, (column - 1) * 20, 0, (row) * 20, (column) * 20, 20.0, false);
}

void startEnd(int column, int row, bool val, bool def)
{
	if (val) {
		glColor3ub(0, 255, 0);
	}
	else {
		glColor3ub(255, 0, 0);
	}
	if (def == true) {
		glBegin(GL_QUADS);
		glVertex2i((row - 1) * 20, (column - 1) * 20);
		glVertex2i((row - 1) * 20, (column) * 20);
		glVertex2i((row) * 20, (column) * 20);
		glVertex2i((row) * 20, (column - 1) * 20);
		glEnd();
	}
}


bool Maze::moveAllowed(int row, int col)
{
	// note order of conditions 
	// (I don't check map[row][col] until I am sure that row and col are valid)
	return (row > 0 && row <= rowSize
		&& col > 0 && col <= colSize
		&& map[row][col]!="1");
}


void Maze::draw(Entity& theEntity)
{
	/*for (int i = 1; i <= 9; ++i)
	{
		for (int j = 1; j <= 9; ++j)
		{
			drawTarget(i, j, map[i][j]);
			
		}
	}*/
	int row = 0;
	int column = 0;
	for (int i = theEntity.getX() - 4; i <= theEntity.getX()+4; i++) {
		row = 0;
		for (int j = theEntity.getY()-4; j <= theEntity.getY()+4; ++j)
		{
			if (i < 1||j<1||i>colSize||j>rowSize) {
				//drawTarget(i, j, "1");
				glColor3ub(0, 0, 0);
			}
			else {
				string val = map[i][j];
				//drawTarget(i, j, map[i][j]);
				if (val == "1") {
					glColor3ub(0, 0, 0);
				}
				else if (val == "d") {
					glColor3ub(100, 0, 0);
				}

				else {
					glColor3ub(255, 255, 255);
				}

			}
			glBegin(GL_QUADS);
			glVertex2i((row - 1) * 20, (column - 1) * 20);
			glVertex2i((row - 1) * 20, (column) * 20);
			glVertex2i((row) * 20, (column) * 20);
			glVertex2i((row) * 20, (column - 1) * 20);
			row++;
			glEnd();

		}
		column++;
	}

}


bool toBool(std::string const& s) {
	if (s == "0") {
		return 0;
	}
	return 1;
}
bool Maze::load()
{
	ifstream inFile;
	string x;
	int k = 0;
	int size;
	int row = 1;
	int column = 1;
	inFile.open(file);
	if (inFile.is_open()) {
		while (true) {
			string x;
			inFile >> x;
			if (inFile.eof()) break;

			if (k == 0) {
				colSize = stoi(x);
				rowSize = stoi(x);
				size = stoi(x);
			}
			else if (k == 1) {
				startX = stoi(x);
			}
			else if (k == 2) {
				startY = stoi(x);
			}
			else if (k == 3) {
				endX = stoi(x);
			}
			else if (k == 4) {
				endY = stoi(x);
			}
			else if (column % (size + 1) == 0 && row < size) {
				row++;
				column = 1;
				map[row][column] = x;
				column++;
			}
			else {
				map[row][column] = x;
				column++;
			}
			k++;
			//cout << startX << "," << startY << " " << endX << "," << endY << endl;

		}
		for (int i = 1; i <= colSize; ++i)
		{
			for (int j = 1; j <= colSize; ++j)
			{
				if (map[i][j] != "1" && map[i][j] != "0" && map[i][j] != "d" && map[i][j] != "e" && map[i][j] != "p" && map[i][j] != "w" && map[i][j] != "k") {
					map[i][j] = "1";
				}
			}
		}
		map[endX][endY] = "0";
		return 1;
	}
	else {
		return 0;
	}
}

vector<vector<string>> Maze::view(Entity& anEntity)
{
	int x = anEntity.getX();
	int y = anEntity.getY();
	vector<vector<string>> v(rowSize+1, vector<string>(colSize+1, "0"));
	for (int i = 0; i <= colSize; ++i)
	{
		for (int j = 0; j <= rowSize; ++j)
		{
			v[i][j] = map[i][j];
		}
	}
	return v;
}

void Maze::print()
{
	std::cout << std::endl;
	for (int i = 0; i <= colSize; ++i)
	{
		for (int j = 0; j <= colSize; ++j)
		{
			std::cout << map[i][j] << ' ';
		}
		std::cout << std::endl;
	}
}

void Maze::edit(int xx, int yy, string val)
{
	map[xx][yy] = val;
}




void Maze::findShortestPath(Enemy& anEnemy,Entity& anEntity)
{
	int rootX, rootY;
	int currX, currY;
	
	vector<parentChild> family;
	vector<vector<int>> visited;
	rootX = anEnemy.getX();
	rootY = anEnemy.getY();
	int entityX = anEntity.getX();
	int entityY = anEntity.getY();
	//cout << entityX << " adf " << entityY << endl;
	if (rootX == entityX && rootY == entityY) {
		return;
	}
	queue<vector<int>> list;
	list.push({ rootX, rootY });
	visited.push_back({ rootX,rootY });
	vector<int> child;
	parentChild pC;

	vector<vector<int>>::iterator it;
	while (!list.empty()) {

		currX = list.front().at(0);
		currY = list.front().at(1);
		list.pop();
		if (currX == entityX && currY == entityY) {
			parentChild currF;
			while ((currX != rootX) || (currY != rootY)) {
				vector<int> curr = { currX,currY };
				for (int i = 0; i < family.size(); i++) {
					currF = family.at(i);
					if (currF.child == curr) {
						currX = currF.parent.at(0);
						currY = currF.parent.at(1);
						//cout << currX << " " << currY << endl;
						if (currX-1 == rootX || currX + 1 == rootX|| currY - 1 == rootY|| currY + 1 == rootY)
							anEnemy.move(currX,currY,*this);
					}
				}
			}
			break;
		}
		else {
			if (currX > 1 && (map[currX - 1][currY] != "1" && map[currX - 1][currY] != "e")) {
				child = { currX - 1,currY };
				it = find(visited.begin(), visited.end(), child);
				if (it == visited.end()) {
					pC.child = child;
					pC.parent = { currX,currY };
					family.push_back(pC);
					list.push(child);
					visited.push_back(child);
				}
			}
			if (currX < rowSize && (map[currX + 1][currY] != "1" && map[currX + 1][currY] != "e")) {
				child = { currX + 1,currY };
				it = find(visited.begin(), visited.end(), child);
				if (it == visited.end()) {
					pC.child = child;
					pC.parent = { currX,currY };
					family.push_back(pC);
					list.push(child);
					visited.push_back(child);
				}
			}

			if (currY > 1 && (map[currX][currY - 1] != "1" && map[currX][currY-1] != "e")) {
				child = { currX,currY - 1 };
				it = find(visited.begin(), visited.end(), child);
				if (it == visited.end()) {
					pC.child = child;
					pC.parent = { currX,currY };
					family.push_back(pC);
					list.push(child);
					visited.push_back(child);
				}
			}

			if (currY < colSize &&( map[currX][currY + 1] != "1" && map[currX][currY+1] != "e")) {
				child = { currX ,currY + 1 };
				it = find(visited.begin(), visited.end(), child);
				if (it == visited.end()) {
					pC.child = child;
					pC.parent = { currX,currY };
					family.push_back(pC);
					list.push(child);
					visited.push_back(child);
				}
			}
		}
	}
}
