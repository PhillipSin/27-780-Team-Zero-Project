#include <stdio.h>
#include <string>
#include <math.h>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include <chrono>
#include "Camera3D.h"
#include "yspng.h"
#include "Enemy.h"
#include "GraphicFont.h"
#include "OrbitingViewer.h"
#include "DrawingUtilNG.h"
#include "maze.h"
#include "yssimplesound.h"
#include <iostream>
#include <vector>
#include "ctime"
#include "algorithm"
#include <fstream>
#include "paths.h"
using namespace std;
using std::vector;


bool keyCheck(Maze map, bool keys, bool moveDown, Entity anEntity) {

	if (anEntity.hasKey() == true) {
		return true;
	}
	if (keys == false) {
		return true;
	}
	if (moveDown!=0) {
		if (keys == true && anEntity.getX()+1 ==  map.getEndX() && anEntity.getY() == map.getEndY()) {
			return false;
		}
	}
	else {
		if (keys == true && anEntity.getX() == map.getEndX() && anEntity.getY()+1 == map.getEndY()) {
			return false;
		}
	}
	
	return true;
}



void drawMap(vector<vector<string>> map, GLuint texId, GLuint texId1, GLuint texId2, GLuint texId3,Maze maze) {
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POLYGON_OFFSET_FILL);
	// bind a texture to OpenGL primitives
	glBindTexture(GL_TEXTURE_2D, texId);   // imageSample (a bird)

	//glBegin(GL_QUADS);
	////int xSize = png.wid * scale1;
	////int ySize = png.hei * scale1;
	//// For each vertex, assign texture coordinate before vertex coordinate.
	//glTexCoord2d(0.0, 0.0);   // these are "percentage" of the image
	//glVertex3d(30, 0, -0.1);        // these are actual pixel coordinates on screen

	//glTexCoord2d(1.0, 0.0);
	//glVertex3d(30 + 5, 0, -0.1);

	//glTexCoord2d(1.0, 1.0);
	//glVertex3d(30 + 5, 0 + 5, -0.1);

	//glTexCoord2d(0.0, 1.0);
	//glVertex3d(30, 0 + 5, -0.1);
	//glEnd();
	int ySize = maze.getCol();
	int xSize = maze.getRow();
	int xEnd = maze.getEndX();
	int yEnd = maze.getEndY();
	for (int i = 0; i<ySize+1; i++) {
		for (int j = 0; j < xSize+1; j++) {
			if (i == yEnd && j == xEnd) {
				glBindTexture(GL_TEXTURE_2D, texId2);
				glColor3ub(112, 112, 112);
				DrawingUtilNG::drawCube((j - 1) * 20, 0, (i - 1) * 20, j * 20, 20.0, i * 20, false);
				glBegin(GL_QUADS);
				//int xSize = png.wid * scale1;
				//int ySize = png.hei * scale1;
				glTexCoord2d(0.0, 0.0);   // these are "percentage" of the image
				glVertex3d((j - 1) * 20, 0, (i) * 20);        // these are actual pixel coordinates on screen

				glTexCoord2d(1.0, 0.0);
				glVertex3d((j - 1) * 20, 20, (i) * 20);

				glTexCoord2d(1.0, 1.0);
				glVertex3d((j - 1) * 20, 20, (i - 1) * 20);

				glTexCoord2d(0.0, 1.0);
				glVertex3d((j - 1) * 20, 0, (i - 1) * 20);
				glEnd();

				glBegin(GL_QUADS);
				//int xSize = png.wid * scale1;
				//int ySize = png.hei * scale1;
				glTexCoord2d(0.0, 0.0);   // these are "percentage" of the image
				glVertex3d((j) * 20, 0, (i) * 20);        // these are actual pixel coordinates on screen

				glTexCoord2d(1.0, 0.0);
				glVertex3d((j) * 20, 20, (i) * 20);

				glTexCoord2d(1.0, 1.0);
				glVertex3d((j) * 20, 20, (i - 1) * 20);

				glTexCoord2d(0.0, 1.0);
				glVertex3d((j) * 20, 0, (i - 1) * 20);
				glEnd();

				glBegin(GL_QUADS);
				//int xSize = png.wid * scale1;
				//int ySize = png.hei * scale1;
				glTexCoord2d(0.0, 0.0);   // these are "percentage" of the image
				glVertex3d((j) * 20, 0, (i) * 20);        // these are actual pixel coordinates on screen

				glTexCoord2d(1.0, 0.0);
				glVertex3d((j) * 20, 20, (i) * 20);

				glTexCoord2d(1.0, 1.0);
				glVertex3d((j - 1) * 20, 20, (i) * 20);

				glTexCoord2d(0.0, 1.0);
				glVertex3d((j - 1) * 20, 0, (i) * 20);
				glEnd();
				glBegin(GL_QUADS);
				//int xSize = png.wid * scale1;
				//int ySize = png.hei * scale1;
				glTexCoord2d(0.0, 0.0);   // these are "percentage" of the image
				glVertex3d((j) * 20, 0, (i - 1) * 20);        // these are actual pixel coordinates on screen

				glTexCoord2d(1.0, 0.0);
				glVertex3d((j) * 20, 20, (i - 1) * 20);

				glTexCoord2d(1.0, 1.0);
				glVertex3d((j - 1) * 20, 20, (i - 1) * 20);

				glTexCoord2d(0.0, 1.0);
				glVertex3d((j - 1) * 20, 0, (i - 1) * 20);
				//glBindTexture(GL_TEXTURE_2D, 0);
				glEnd();
			}
			if (map[i][j] == "1") {
				glBindTexture(GL_TEXTURE_2D, texId);
				glColor3ub(112, 112, 112);
				DrawingUtilNG::drawCube((j - 1) * 20, 0, (i - 1) * 20, j * 20, 20.0, i * 20, false);
				glBegin(GL_QUADS);
				//int xSize = png.wid * scale1;
				//int ySize = png.hei * scale1;
				glTexCoord2d(0.0, 0.0);   // these are "percentage" of the image
				glVertex3d((j - 1) * 20, 0, (i) * 20);        // these are actual pixel coordinates on screen

				glTexCoord2d(1.0, 0.0);
				glVertex3d((j - 1) * 20, 20, (i) * 20);

				glTexCoord2d(1.0, 1.0);
				glVertex3d((j - 1) * 20, 20, (i - 1) * 20);

				glTexCoord2d(0.0, 1.0);
				glVertex3d((j - 1) * 20, 0, (i - 1) * 20);
				glEnd();

				glBegin(GL_QUADS);
				//int xSize = png.wid * scale1;
				//int ySize = png.hei * scale1;
				glTexCoord2d(0.0, 0.0);   // these are "percentage" of the image
				glVertex3d((j) * 20, 0, (i) * 20);        // these are actual pixel coordinates on screen

				glTexCoord2d(1.0, 0.0);
				glVertex3d((j) * 20, 20, (i) * 20);

				glTexCoord2d(1.0, 1.0);
				glVertex3d((j) * 20, 20, (i - 1) * 20);

				glTexCoord2d(0.0, 1.0);
				glVertex3d((j) * 20, 0, (i - 1) * 20);
				glEnd();

				glBegin(GL_QUADS);
				//int xSize = png.wid * scale1;
				//int ySize = png.hei * scale1;
				glTexCoord2d(0.0, 0.0);   // these are "percentage" of the image
				glVertex3d((j) * 20, 0, (i) * 20);        // these are actual pixel coordinates on screen

				glTexCoord2d(1.0, 0.0);
				glVertex3d((j) * 20, 20, (i) * 20);

				glTexCoord2d(1.0, 1.0);
				glVertex3d((j-1) * 20, 20, (i) * 20);

				glTexCoord2d(0.0, 1.0);
				glVertex3d((j-1) * 20, 0, (i) * 20);
				glEnd();
				glBegin(GL_QUADS);
				//int xSize = png.wid * scale1;
				//int ySize = png.hei * scale1;
				glTexCoord2d(0.0, 0.0);   // these are "percentage" of the image
				glVertex3d((j) * 20, 0, (i-1) * 20);        // these are actual pixel coordinates on screen

				glTexCoord2d(1.0, 0.0);
				glVertex3d((j) * 20, 20, (i-1) * 20);

				glTexCoord2d(1.0, 1.0);
				glVertex3d((j - 1) * 20, 20, (i-1) * 20);

				glTexCoord2d(0.0, 1.0);
				glVertex3d((j - 1) * 20, 0, (i-1) * 20);
				//glBindTexture(GL_TEXTURE_2D, 0);
				glEnd();
			}
			else if (map[i][j] == "d") {
				glColor3ub(100, 1, 5);
				DrawingUtilNG::drawCube((j - 1) * 20, 0, (i - 1) * 20, j * 20, 20.0, i * 20, false);
			}
			else if (map[i][j] == "e") {

				glColor3ub(255, 0, 0);
				DrawingUtilNG::drawCube((j - 1) * 20 + 5, 0, (i - 1) * 20 + 5, j * 20 - 5, 10.0, i * 20 - 5, false);
				glColor3ub(69, 69, 69);
				DrawingUtilNG::drawCube((j - 1) * 20, -1, (i - 1) * 20, j * 20, 0, i * 20, false);

				glBindTexture(GL_TEXTURE_2D, texId1);
				glBegin(GL_QUADS);
				//int xSize = png.wid * scale1;
				//int ySize = png.hei * scale1;
				glTexCoord2d(0.0, 0.0);   // these are "percentage" of the image
				glVertex3d((j - 1) * 20, 0, (i) * 20);        // these are actual pixel coordinates on screen

				glTexCoord2d(1.0, 0.0);
				glVertex3d((j - 1) * 20, 10, (i) * 20);

				glTexCoord2d(1.0, 1.0);
				glVertex3d((j - 1) * 20, 10, (i - 1) * 20);

				glTexCoord2d(0.0, 1.0);
				glVertex3d((j - 1) * 20, 0, (i - 1) * 20);
				glEnd();

				glBegin(GL_QUADS);
				//int xSize = png.wid * scale1;
				//int ySize = png.hei * scale1;
				glTexCoord2d(0.0, 0.0);   // these are "percentage" of the image
				glVertex3d((j) * 20, 0, (i) * 20);        // these are actual pixel coordinates on screen

				glTexCoord2d(1.0, 0.0);
				glVertex3d((j) * 20, 10, (i) * 20);

				glTexCoord2d(1.0, 1.0);
				glVertex3d((j) * 20, 10, (i - 1) * 20);

				glTexCoord2d(0.0, 1.0);
				glVertex3d((j) * 20, 0, (i - 1) * 20);
				glEnd();

				glBegin(GL_QUADS);
				//int xSize = png.wid * scale1;
				//int ySize = png.hei * scale1;
				glTexCoord2d(0.0, 0.0);   // these are "percentage" of the image
				glVertex3d((j) * 20, 0, (i) * 20);        // these are actual pixel coordinates on screen

				glTexCoord2d(1.0, 0.0);
				glVertex3d((j) * 20, 10, (i) * 20);

				glTexCoord2d(1.0, 1.0);
				glVertex3d((j - 1) * 20, 10, (i) * 20);

				glTexCoord2d(0.0, 1.0);
				glVertex3d((j - 1) * 20, 0, (i) * 20);
				glEnd();
				glBegin(GL_QUADS);
				//int xSize = png.wid * scale1;
				//int ySize = png.hei * scale1;
				glTexCoord2d(0.0, 0.0);   // these are "percentage" of the image
				glVertex3d((j) * 20, 0, (i - 1) * 20);        // these are actual pixel coordinates on screen

				glTexCoord2d(1.0, 0.0);
				glVertex3d((j) * 20, 10, (i - 1) * 20);

				glTexCoord2d(1.0, 1.0);
				glVertex3d((j - 1) * 20, 10, (i - 1) * 20);

				glTexCoord2d(0.0, 1.0);
				glVertex3d((j - 1) * 20, 0, (i - 1) * 20);
				glEnd();
				//glBindTexture(GL_TEXTURE_2D, 0);
				
			}
			else if (map[i][j] == "p") {
				glColor3ub(109, 237, 224);
				DrawingUtilNG::drawCube((j - 1) * 20 + 5, 0, (i - 1) * 20 + 5, j * 20 - 5, 5, i * 20 - 5, false);
				glColor3ub(0, 0, 0);
				DrawingUtilNG::drawCube((j - 1) * 20, -1, (i - 1) * 20, j * 20, 0, i * 20, false);
			}
			else if (map[i][j] == "w") {
				glColor3ub(128, 128, 128);
				DrawingUtilNG::drawCube((j - 1) * 20 + 5, 0, (i - 1) * 20 + 5, j * 20 - 5, 5, i * 20 - 5, false);
				glColor3ub(0, 0, 0);
				DrawingUtilNG::drawCube((j - 1) * 20, -1, (i - 1) * 20, j * 20, 0, i * 20, false);
			}
			else if (map[i][j] == "k") {
			glColor3ub(255, 216, 107);
			DrawingUtilNG::drawCube((j - 1) * 20 + 5, 0, (i - 1) * 20 + 5, j * 20 - 5, 5, i * 20 - 5, false);
			glColor3ub(0, 0, 0);
			DrawingUtilNG::drawCube((j - 1) * 20, -1, (i - 1) * 20, j * 20, 0, i * 20, false);
			}

			else {
				glColor3ub(0, 0, 0);
				DrawingUtilNG::drawCube((j - 1) * 20, -1, (i - 1) * 20, j * 20, 0, i * 20, false);
				//DrawingUtilNG::drawCube((j - 1) * 20, 20, (i - 1) * 20, j * 20, 21, i * 20, false);
			}	
			
		}
	}

}

bool addKeys(Maze map, int xSize, int ySize) {
	bool key = false;
	for (int i = 0; i < ySize + 1; i++) {
		for (int j = 0; j < xSize + 1; j++) {
			if (map.getMap(i, j) == "k") {
				key = true;
			}
		}
	}
	return key;
}

vector<Enemy> addEnemies(Maze map,int xSize,int ySize) {
	vector<Enemy> theEnemies;
	for (int i = 0; i < ySize + 1; i++) {
		for (int j = 0; j < xSize + 1; j++) {
			if (map.getMap(i,j) == "e") {
				theEnemies.push_back(Enemy(i, j));
			}
		}
	}
	return theEnemies;
}

int main(void){

	double elapsedTime;
	auto begin = std::chrono::high_resolution_clock::now();

	YsSoundPlayer player;
	YsSoundPlayer::SoundData wav;
	YsSoundPlayer::SoundData wavh;
	YsSoundPlayer::SoundData wavy;
	YsSoundPlayer::SoundData wavs;
	YsSoundPlayer::SoundData wavstep;
	YsSoundPlayer::SoundData wavdr;
	YsSoundPlayer::SoundData wavoof;
	YsSoundPlayer::SoundData wavdoor;
	player.Start();
	wav.LoadWav("golf_swing.wav");
	wavh.LoadWav("metal_crunch.wav");
	wavy.LoadWav("yay_z.wav");
	wavs.LoadWav("scream_male.wav");
	wavdr.LoadWav("slurp.wav");
	wavstep.LoadWav("footsteps.wav");
	wavoof.LoadWav("oof.wav");
	wavdoor.LoadWav("door_creak.wav");
	vector<Maze> mazeList;
	vector<Enemy> theEnemies;
	bool terminate = false;
	Camera3D camera;
	OrbitingViewer orbit;
	vector<vector<string>> viewer;

	srand(time(NULL));
	//camera.z = 10.0;
	for (int i = 0; i < 5; i++) {
		paths s;
		int map_size = 15;
		int height = map_size;
		int width = map_size;
		s.init(height, width);
		
		vector<char> row(width);
		vector<vector<char>> map;
		for (int i = 0; i < height; ++i)
		{
			map.push_back(row);
		}
		s.maze(map);

		s.placeItems(map);
		//s.showMaze(map);
		s.save_map(map, to_string(i+1)+".txt");
	}
	Maze theMaze("testMap.txt");
	//Maze theMaze("1.txt");
	Maze theMaze1("testMap1.txt");
	Maze theMaze2("1.txt");
	Maze theMaze3("2.txt");
	//Maze theMaze4("3.txt");
	//Maze theMaze5("4.txt");

	mazeList.push_back(theMaze);
	mazeList.push_back(theMaze1);
	mazeList.push_back(theMaze2);
	mazeList.push_back(theMaze3);
	//mazeList.push_back(theMaze4);
	//mazeList.push_back(theMaze5);

	//theMaze.load();
	
	FsOpenWindow(16, 16, 1200, 800, 1);

	mazeList[0].load();
	mazeList[1].load();
	mazeList[2].load();
	mazeList[3].load();
	//mazeList[4].load();
	//mazeList[5].load();

	bool keys;

	theEnemies = addEnemies(mazeList[0], mazeList[0].getCol(), mazeList[0].getRow());
	keys = addKeys(mazeList[0], mazeList[0].getCol(), mazeList[0].getRow());
	//initialize special fonts (after FsOpenWindow)
	ComicSansFont comicsans;
	comicsans.setColorHSV(300, 1, 1);
	ImpactFont impact;
	impact.setColorRGB(255,255,255);
	//shit here
	YsRawPngDecoder png[4];
	png[0].Decode("face.png");
	png[1].Decode("wall.png");
	png[2].Decode("exit.png");
	png[3].Decode("wall.png");


	GLuint texId[4];  // this will be use as texture identifiers for the two PNGs

	// glGenTextures(2,texId);  // You can also reserve two texture identifies with one call this way.

	glGenTextures(1, &texId[0]);  // Reserve one texture identifier
	glBindTexture(GL_TEXTURE_2D, texId[0]);  // Making the texture identifier current (or bring it to the deck)

	// set up parameters for the current texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D
	(GL_TEXTURE_2D,
		0,    // Level of detail
		GL_RGBA,
		png[0].wid,
		png[0].hei,
		0,    // Border width, but not supported and needs to be 0.
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		png[0].rgba);

	glGenTextures(1, &texId[1]);  // Reserve texture identifier for other PNG
	glBindTexture(GL_TEXTURE_2D, texId[1]);  // Making the texture identifier current (or bring it to the deck)

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D
	(GL_TEXTURE_2D,
		0,
		GL_RGBA,
		png[1].wid,
		png[1].hei,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		png[1].rgba);

	glGenTextures(1, &texId[2]);  // Reserve texture identifier for other PNG
	glBindTexture(GL_TEXTURE_2D, texId[2]);  // Making the texture identifier current (or bring it to the deck)

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D
	(GL_TEXTURE_2D,
		0,
		GL_RGBA,
		png[2].wid,
		png[2].hei,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		png[2].rgba);

	glGenTextures(1, &texId[3]);  // Reserve texture identifier for other PNG
	glBindTexture(GL_TEXTURE_2D, texId[3]);  // Making the texture identifier current (or bring it to the deck)

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D
	(GL_TEXTURE_2D,
		0,
		GL_RGBA,
		png[3].wid,
		png[3].hei,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		png[3].rgba);

	double angle = 0.0;
	int key;
	Entity theEntity(mazeList[0].getStartX(), mazeList[0].getStartY(),3);
	
	int mazeNow = 0;
	bool newMaze = true;
	string textToPrint = "";
	string textToPrint1 = "";
	double nTime = 0;

	while (FSKEY_SPACE != (key = FsInkey())) {
		FsPollDevice();
		int wid, hei;
		FsGetWindowSize(wid, hei);

		glClearColor(0, 0, 0, 0);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		impact.drawText("Welcome to Dungeon Zero", 50, 80, .45);
		impact.drawText("The goal is to get as deep into the dungeon as possible", 50, 120, .45);
		impact.drawText("Use Arrow Keys to move", 50, 250, .45);
		impact.drawText("Press A to attack", 50, 290, .45);
		impact.drawText("Press S to drink potions you may have", 50, 330, .45);
		impact.drawText("Press D to pick up items you're on", 50, 370, .45);
		impact.drawText("Press Space to start the game", 50, 600, .45);


		FsSwapBuffers();
		FsSleep(10);
	}


	mazeList[0].print();

	while (FSKEY_ESC != (key = FsInkey()))
	{
		

		elapsedTime = chrono::duration_cast<chrono::milliseconds>
			(std::chrono::high_resolution_clock::now() - begin).count();


		FsPollDevice();

		int wid, hei;
		FsGetWindowSize(wid, hei);
		//cout << mazeNow << " " << mazeList.size()<<endl;
		
		if (theEntity.reachedGoal(mazeList[mazeNow])) {
			mazeNow++;
			if (mazeNow == mazeList.size()) {
				cout << "You've finished the dungeon!";
				break;
				//return 0;
			}
			newMaze = true;
			player.PlayOneShot(wavdoor);
			//player.PlayOneShot(wavy);
			textToPrint = "Welcome to level " + to_string(mazeNow+1);
			nTime = elapsedTime;
			theEntity.setKey();
		}
		else {
			newMaze = false;
		}

		if (newMaze == true) {
			mazeList[mazeNow].print();
			
			keys = addKeys(mazeList[mazeNow], mazeList[mazeNow].getCol(), mazeList[mazeNow].getRow());
			theEnemies = addEnemies(mazeList[mazeNow], mazeList[mazeNow].getCol(), mazeList[mazeNow].getRow());
			theEntity.changePos(mazeList[mazeNow].getStartX(), mazeList[mazeNow].getStartY());
			camera.x = mazeList[mazeNow].getStartY()*20-10;
			camera.z = mazeList[mazeNow].getStartX()*20-10;
			int playX = mazeList[mazeNow].getStartX();
			int playY = mazeList[mazeNow].getStartY();
			if (mazeList[mazeNow].getMap(playX+1,playY) == "0") {
				theEntity.setDirection(3);
				camera.h = -3.141592;
			}
			else if (mazeList[mazeNow].getMap(playX,playY+1) == "0") {
				theEntity.setDirection(0);
				camera.h = -3.141592/2;
			}

			newMaze = false;
		}


		int key = FsInkey();
		switch (key)
		{
		case FSKEY_ESC:
			terminate = true;
			break;
		}
		if (FSKEY_UP <= key && key <= FSKEY_RIGHT) // Task 3
			if (key == 67) { //up
				switch (theEntity.getDirection()) {
				case 0:
					if (keyCheck(mazeList[mazeNow], keys, 0, theEntity)) {
						if (theEntity.moveRight(mazeList[mazeNow])) {
							camera.x += 20;
						}
					}
					else {
						textToPrint1 = "You need a key to keep going .";
						nTime = elapsedTime;
					}
					break;
				case 1:
					if (theEntity.moveUp(mazeList[mazeNow])) {
						camera.z -= 20;
					}
					break;
				case 2:
					if (theEntity.moveLeft(mazeList[mazeNow])) {
						camera.x -= 20;
					}
					break;
				case 3:
					if (keyCheck(mazeList[mazeNow], keys, 1, theEntity)) {
						if (theEntity.moveDown(mazeList[mazeNow])) {
							camera.z += 20;

						}
					}
					else {
						textToPrint1 = "You need a key to keep going .";
						nTime = elapsedTime;
					}
					break;
				}
				player.PlayOneShot(wavstep);
				for (int i = 0; i < theEnemies.size(); i++) {
					mazeList[mazeNow].findShortestPath(theEnemies[i], theEntity);
					bool pHit = theEnemies[i].attack(theEntity);
					if (pHit) {
						textToPrint1 = "A monster strikes at you.";
						//cout << "hit by " << i << endl;
						nTime = elapsedTime;
						player.PlayOneShot(wavoof);
					}
				}
			}
			else if (key == 69) { //left
				camera.h += Camera3D::PI / 2;
				theEntity.changeDirection(1);
			}
			else if (key== 70){ //right
				camera.h -= Camera3D::PI / 2;
				theEntity.changeDirection(0);
			}

		if (key == FSKEY_A) //attack
		{
			player.PlayOneShot(wav);
			for (int i = 0; i < theEnemies.size(); i++) {
				bool hit = theEntity.attack(theEntity.getX(), theEntity.getY(), mazeList[mazeNow], theEnemies[i]);


				mazeList[mazeNow].findShortestPath(theEnemies[i], theEntity);
				if (hit) {
					textToPrint = "You strike at the monster.";
					player.PlayOneShot(wavh);
					nTime = elapsedTime;
				}

				if (theEnemies[i].getHealth() <= 0) {
					textToPrint = "You defeat the monster.";
					nTime = elapsedTime;
					player.PlayOneShot(wavs);
					theEnemies.erase(theEnemies.begin() + i);
					//do something
				}
				else {
					bool pHit = theEnemies[i].attack(theEntity);
					if (pHit) {
						textToPrint1 = "A monster strikes at you.";
						//cout << "hit by " << i << endl;
						nTime = elapsedTime;
						player.PlayOneShot(wavoof);
					}
				}
				
			}
		}

		if (key == FSKEY_S)//consume potion
		{
			bool drunk = theEntity.drink();
			if (drunk) {
				player.PlayOneShot(wavdr);
				textToPrint = "You chug some drink. You feel healthier.";
				nTime = elapsedTime;
			}
			else {
				textToPrint = "You feel parched but have nothing to sate your thirst.";
				nTime = elapsedTime;
			}
			for (int i = 0; i < theEnemies.size(); i++) {
				mazeList[mazeNow].findShortestPath(theEnemies[i], theEntity);
				bool pHit = theEnemies[i].attack(theEntity);
				if (pHit) {
					textToPrint1 = "A monster strikes at you.";
					//cout << "hit by " << i << endl;
					nTime = elapsedTime;
					player.PlayOneShot(wavoof);
				}
			}

		}

		if (key == FSKEY_D) //item pickup
		{
			int item = theEntity.pickUp(theEntity.getX(), theEntity.getY(), mazeList[mazeNow]);
			if (item == 0) {
				textToPrint = "You pick up a bottle of some kind of liquid.";
				nTime = elapsedTime;
			}
			else if (item == 1) {
				textToPrint = "You pick up something sharp and pointy.";
				nTime = elapsedTime;
			}
			else if (item == 2) {
				textToPrint = "You bend down only to realize there's nothing for you to pick up.";
				nTime = elapsedTime;
			}
			else if (item == 3) {
				textToPrint = "You find a key.";
				nTime = elapsedTime;
			}
			for (int i = 0; i < theEnemies.size(); i++) {
				mazeList[mazeNow].findShortestPath(theEnemies[i], theEntity);
				bool pHit = theEnemies[i].attack(theEntity);
				if (pHit) {
					textToPrint1 = "A monster strikes at you.";
					//cout << "hit by " << i << endl;
					nTime = elapsedTime;
					player.PlayOneShot(wavoof);
				}
			}
		}

		if (theEntity.checkBelow(mazeList[mazeNow])) {
			textToPrint = "You notice something below you.";
			nTime = elapsedTime;
		}
		//else if (!theEntity.checkBelow(mazeList[mazeNow]) && elapsedTime < nTime + 500) {
		//	textToPrint = "";
		//}

		if (elapsedTime > nTime + 1500.0) {
			textToPrint = "";
			textToPrint1 = "";
		}
		if (theEntity.getHealth() <= 0) {
			cout << "You died" << endl;
			break;
		}

		camera.setUpCameraProjection();
		camera.setUpCameraTransformation();

		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glClearColor(0, 0, 0, 0);
		glViewport(0, 0, wid, hei);

		// Set up 3D drawing
		camera.setUpCameraProjection();
		camera.setUpCameraTransformation();

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(1, 1);

		// 3D drawing from here
		glColor3ub(93, 290, 112);
		//cout << mazeNow;
		viewer = mazeList[mazeNow].view(theEntity);
		drawMap(viewer, texId[1], texId[0], texId[2], texId[3],mazeList[mazeNow]);

		
		// draw axes

		//comicsans.drawText3D("  Hello World", { 0,-20,0 }, { 0,10,0 }, { -1,-20,-1 }, .3, 20.);

		// Set up 2D drawing
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, (float)wid - 1, (float)hei - 1, 0, -1, 1);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glDisable(GL_DEPTH_TEST);
		mazeList[mazeNow].draw(theEntity);

		

		string healthText = "Health: "+ to_string(theEntity.getHealth());
		string potText = "Potions: " + to_string(theEntity.getNumPotions());
		//string weapText = "Weapons: " + to_string(theEntity.getHealth());
		impact.drawText(healthText, 50, 700, .35);
		impact.drawText(potText, 50, 750, .35);
		//impact.drawText(weapText, 50, 750, .35);

		//comicsans.drawText(to_string(camera.x), 400, 40, .25);
		//comicsans.drawText(to_string(camera.h), 600, 60, .25);
		impact.drawText(textToPrint, 400, 80, .45);
		impact.drawText(textToPrint1, 400, 120, .45);
		theEntity.draw();
		FsSwapBuffers();
		FsSleep(10);
	}
	return 0;

}