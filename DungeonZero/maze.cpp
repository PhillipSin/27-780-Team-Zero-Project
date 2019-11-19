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
void Maze::draw()
{
	for (int i = 1; i <= colSize; ++i)
	{
		for (int j = 1; j <= colSize; ++j)
		{
			drawTarget(i, j, map[i][j]);
		}
	}
	startEnd(startX, startY, 1, startDef);
	startEnd(endX, endY, 0, endDef);
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

		}
		for (int i = 1; i <= colSize; ++i)
		{
			for (int j = 1; j <= colSize; ++j)
			{
				if (map[i][j] != "1" && map[i][j] != "0" && map[i][j] != "d" && map[i][j] != "e") {
					map[i][j] = "1";
				}
			}
		}
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
	vector<vector<string>>viewer{ {"0","0","0","0","0","0","0","0","0","0"},
							   {"0","0","0","0","0","0","0","0","0","0"}, 
	{"0","0","0","0","0","0","0","0","0","0"}, 
	{"0","0","0","0","0","0","0","0","0","0"}, 
	{"0","0","0","0","0","0","0","0","0","0"}, 
	{"0","0","0","0","0","0","0","0","0","0"}, 
	{"0","0","0","0","0","0","0","0","0","0"}, 
	{"0","0","0","0","0","0","0","0","0","0"}, 
	{"0","0","0","0","0","0","0","0","0","0"}, 
	{"0","0","0","0","0","0","0","0","0","0"}};
	for (int i = 0; i <= colSize; ++i)
	{
		for (int j = 0; j <= rowSize; ++j)
		{
				v[i][j] = map[i][j];
				cout << v[i][j] << " ";
		}
		cout << endl;
		
	}
	cout << endl;
	return v;
}

void Maze::print()
{
	std::cout << std::endl;
	for (int i = 1; i <= colSize; ++i)
	{
		for (int j = 1; j <= colSize; ++j)
		{
			std::cout << map[i][j] << ' ';
		}
		std::cout << std::endl;
	}
}



//void Maze::save()
//{
//	string fileN;
//	cout << "Filename: ";
//	cin >> fileN;
//	ofstream outfile(fileN);
//	string line1 = to_string(colSize);
//	string line2 = to_string(startX) + " " + to_string(startY);
//	string line3 = to_string(endX) + " " + to_string(endY);
//	outfile << line1 << endl << line2 << endl << line3;
//	//cout << line1 << endl << line2 << endl << line3;
//
//	outfile << std::endl;
//	for (int i = 1; i <= colSize; ++i)
//	{
//		for (int j = 1; j <= colSize; ++j)
//		{
//			outfile << map[i][j] << ' ';
//		}
//		outfile << std::endl;
//	}
//	outfile.close();
//}

//void Maze::edit(int locY, int locX)
//{
//
//	int i = locX / 20 + 1;
//	int j = locY / 20 + 1;
//
//	if (map[i][j] == 0) {
//		map[i][j] = 1;
//
//		if (i == startX && j == startY) {
//			startDef = false;
//			if (endDef == false) {
//				endX = i;
//				endY = j;
//				endDef = true;
//			}
//			else {
//				map[i][j] = 0;
//			}
//		}
//		else if (i == endX && j == endY) {
//			endDef = false;
//			map[i][j] = 0;
//		}
//
//	}
//	else if (map[i][j] == 1) {
//		map[i][j] = 0;
//		if (startDef == false) {
//			startX = i;
//			startY = j;
//			startDef = true;
//		}
//		else if (startDef == true && endDef == false) {
//			endX = i;
//			endY = j;
//			endDef = true;
//		}
//	}
//
//}
//void drawPath(int column, int row) {
//
//	glColor3ub(100, 150, 100);
//
//
//	glBegin(GL_QUADS);
//	glVertex2i((row - 1) * 20, (column - 1) * 20);
//	glVertex2i((row - 1) * 20, (column) * 20);
//	glVertex2i((row) * 20, (column) * 20);
//	glVertex2i((row) * 20, (column - 1) * 20);
//	glEnd();
//}

//void Maze::findShortestPath(Entity& anEntity)
//{
//	int rootX, rootY;
//	int currX, currY;
//	vector<parentChild> family;
//	vector<vector<int>> visited;
//	rootX = anEntity.getX();
//	rootY = anEntity.getY();
//	if (rootX == endX && rootY == endY) {
//		return;
//	}
//	queue<vector<int>> list;
//	list.push({ rootX, rootY });
//	visited.push_back({ rootX,rootY });
//	vector<int> child;
//	parentChild pC;
//
//	vector<vector<int>>::iterator it;
//
//	while (!list.empty()) {
//
//		currX = list.front().at(0);
//		currY = list.front().at(1);
//		list.pop();
//		if (currX == endX && currY == endY) {
//			parentChild currF;
//			while ((currX != rootX) || (currY != rootY)) {
//				vector<int> curr = { currX,currY };
//				for (int i = 0; i < family.size(); i++) {
//					currF = family.at(i);
//					if (currF.child == curr) {
//						currX = currF.parent.at(0);
//						currY = currF.parent.at(1);
//						drawPath(currX, currY);
//					}
//				}
//			}
//			break;
//		}
//		else {
//			if (currX > 1 && map[currX - 1][currY] == 0) {
//				child = { currX - 1,currY };
//				it = find(visited.begin(), visited.end(), child);
//				if (it == visited.end()) {
//					pC.child = child;
//					pC.parent = { currX,currY };
//					family.push_back(pC);
//					list.push(child);
//					visited.push_back(child);
//				}
//			}
//
//			if (currX < rowSize && map[currX + 1][currY] == 0) {
//				child = { currX + 1,currY };
//				it = find(visited.begin(), visited.end(), child);
//				if (it == visited.end()) {
//					pC.child = child;
//					pC.parent = { currX,currY };
//					family.push_back(pC);
//					list.push(child);
//					visited.push_back(child);
//				}
//			}
//
//			if (currY > 1 && map[currX][currY - 1] == 0) {
//				child = { currX,currY - 1 };
//				it = find(visited.begin(), visited.end(), child);
//				if (it == visited.end()) {
//					pC.child = child;
//					pC.parent = { currX,currY };
//					family.push_back(pC);
//					list.push(child);
//					visited.push_back(child);
//				}
//			}
//
//			if (currY < colSize && map[currX][currY + 1] == 0) {
//				child = { currX ,currY + 1 };
//				it = find(visited.begin(), visited.end(), child);
//				if (it == visited.end()) {
//					pC.child = child;
//					pC.parent = { currX,currY };
//					family.push_back(pC);
//					list.push(child);
//					visited.push_back(child);
//				}
//			}
//		}
//	}
//}
