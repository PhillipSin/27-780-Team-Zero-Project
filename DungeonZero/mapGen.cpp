//The following code will generate a textfile "testmap.txt" with the necessary entity/item positions
#include <iostream>
#include <string>

#include "paths.h"
#include <vector>
#include "ctime"
#include <iostream>
#include "algorithm"
#include <fstream>
#include "paths.h"
#include <stdio.h>

using namespace std;
using std::vector;


int main(int argc, char const* argv[])
{
	paths s;
	int map_size = 20;
	int height = map_size;
	int width = map_size;
	s.init(height, width);
	srand(time(0));
	vector<char> row(width);
	vector<vector<char>> map;
	for (int i = 0; i < height; ++i)
	{
		map.push_back(row);
	}
	s.maze(map);

	s.placeItems(map);
	//s.showMaze(map);
	s.save_map(map);
	return 0;
}