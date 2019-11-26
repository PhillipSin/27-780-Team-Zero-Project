#pragma once

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
using std::vector;

class paths {
private:
	int width, height; // the size of the bitmap
	std::vector<char> enem;

	
	std::vector<char> potion;

	
	std::vector<char> weapon;

	std::vector<char> key;

	//int Enem, potion, weapon, key;
	vector <char> items;
//	vector <int> item_pos;
	char* pixels; // the values of each of the pixels (stored in a 1D array)
	const string fileToSave = "testmap.txt";
	//static unsigned char colors[8][3]; // shared by all CharBitmap objects
	//void loadColors();

public:
	static const int PIXELMAG;
	paths();  // default constructor of class
	~paths();  // destructor of class

	void init(int h, int w);
	void cleanUp();   // used to reset and free up all space used by object
	void maze(vector<vector<char>>& map);
	void showMaze(vector<vector<char>>& map);
	void makeMaze(vector<vector<char>>& map, int i, int j);
	int countVisitedNeighbor(vector<vector<char>>& map, int i, int j);
	void placeItems(vector<vector<char>>& map);
	void shuffle(int a[], int n);
	void swap(int& a, int& b);
	bool save_map(vector<vector<char>>& map);

//	void save(const string fName) const;  // save a bitmap to a file


};