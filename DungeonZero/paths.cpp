//#include "string"
#include "vector"
#include "unordered_map"
#include "queue"
#include "cstdlib"
#include "ctime"
#include <iostream>
#include "algorithm"
#include "stack"
#include <fstream>
#include <cctype>
#include "paths.h"
#include <stdio.h>
#include <string>


using namespace std;

paths::~paths() // destructor of class
{
	cleanUp();
}

void paths::cleanUp()
{
	delete[] pixels;
}
paths::paths()
{
	pixels = new char[width * height];
	width = height = 0;
}
void paths::maze(vector<vector<char>>& map) {
	//U unvisited, ' ' visited
	for (int i = 0; i < map.size(); ++i)
	{
		for (int j = 0; j < map[0].size(); ++j)
		{
			map[i][j] = '1';
		}
	}
	makeMaze(map, 0, 0);
}
void paths::showMaze(vector<vector<char>>& map) {
	for (int i = 0; i < map.size(); ++i)
	{
		for (int j = 0; j < map[0].size(); ++j)
		{
			cout << map[i][j];
		}
		cout << endl;
	}
}
void paths::init(int h, int w)
{
	width = w;
	height = h;
	//Enem =;
	//potion = w * h / 100;
	//weapon = w * h / 200;
	//key = w * h / 200;
	enem.assign(w * h / 100, 'e');
	potion.assign(w * h / 100, 'p');
	weapon.assign(w * h / 100, 'w');
	key.assign(w * h / 100, 'k');
	//items = { enem, potion, weapon, key };
	enem.insert(enem.end(), potion.begin(), potion.end());
	enem.insert(enem.end(), weapon.begin(), weapon.end());
	enem.insert(enem.end(), key.begin(), key.end());

	//items.push_back(enem[1]);
	//cout << "Enemies: " << enem << endl;
	//vector <char> items(width*height);
	//items = { string(Enem, 'e'), string(potion,'p'), string(weapon,'w'), string(key,'k' )};
	const size_t nonPaddedSize = enem.size();
	const size_t numPaddingElements = (100 - nonPaddedSize % 100) % 100;
	if (numPaddingElements > 0)
		enem.resize(nonPaddedSize + numPaddingElements, '0');

	//for (int i = 0; i < 100; ++i)
	//{
	//	cout << "items: " << enem[i] << endl;
	//	//coeffs.push_back(fcoefs[j]);
	//}
}

void paths::placeItems(vector<vector<char>>& map) {
	
	srand(time(NULL));
	int ct = 0;
	for (int i = 0; i < map.size(); ++i)
	{
		for (int j = 0; j < map[0].size(); ++j)
		{
			int randInd = rand() % 100;
			if (map[i][j] == '0')
			{
				//cout << "items: " << endl;
				map[i][j] = enem[randInd];
			}
		}
	}
}

//Use DFS
void paths::makeMaze(vector<vector<char>>& map, int i, int j) {
	int direct[][2] = { {0,1}, {0,-1}, {-1,0}, {1,0} };
	int visitOrder[] = { 0,1,2,3 };
	//out of boundaryg
	if (i < 0 || j < 0 || i >= map.size() || j >= map[0].size())
	{
		return;
	}
#ifdef DEBUG
	cout << "(" << i << ", " << j << ")" << endl;
#endif
	//visited, go back the the coming direction, return 
	if (map[i][j] == '0')
	{
		return;
	}
	//some neighbors are visited in addition to the coming direction, return
	//this is to avoid circles in maze
	if (countVisitedNeighbor(map, i, j) > 1)
	{
		return;
	}
	map[i][j] = '0'; // visited
	//shuffle the visitOrder
	shuffle(visitOrder, 4);
	for (int k = 0; k < 4; ++k)
	{
		int ni = i + direct[visitOrder[k]][0];
		int nj = j + direct[visitOrder[k]][1];
		makeMaze(map, ni, nj);
	}
}
int paths::countVisitedNeighbor(vector<vector<char>>& map, int i, int j)
{
	int direct[][2] = { {1,0}, {-1,0}, {0,1}, {0,-1} };
	int count = 0;
	for (int k = 0; k < 4; ++k)
	{
		int ni = i + direct[k][0];
		int nj = j + direct[k][1];
		//out of boundary
		if (ni < 0 || nj < 0 || ni >= map.size() || nj >= map[0].size())
		{
			continue;
		}
		if (map[ni][nj] == '0')
		{
			count++;//visited
		}
	}
	return count;
}
void paths::shuffle(int a[], int n) {
	for (int i = 0; i < n; ++i)
	{
		swap(a[i], a[rand() % n]);
	}
}
void paths::swap(int& a, int& b) {
	int c = a;
	a = b;
	b = c;
}

bool paths::save_map(vector<vector<char>>& map)
{
	ofstream outFile; // output file stream

	outFile.open(fileToSave);

	if (outFile.is_open()) { // may not have found file
		outFile << width << " " << height << endl;
		outFile << 1 << " " << 1 << endl;
		outFile << width << " " << height << endl;



		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++)
				outFile << map[i][j];
			outFile << endl;
		}
		outFile.close();
		return true;
	}
	else {
		cout << "Cannot open " << fileToSave << " for input.";
		return false;
	}
}


