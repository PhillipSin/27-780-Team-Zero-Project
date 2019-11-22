#include <stdio.h>
#include <math.h>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "Camera3D.h"
#include "yspng.h"
#include "GraphicFont.h"
#include "OrbitingViewer.h"
#include "DrawingUtilNG.h"
#include "maze.h"
#include <iostream>

void drawMap(vector<vector<string>> map, GLuint texId,int xSize,int ySize) {
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POLYGON_OFFSET_FILL);
	// bind a texture to OpenGL primitives
	glBindTexture(GL_TEXTURE_2D, texId);   // imageSample (a bird)

	glBegin(GL_QUADS);
	//int xSize = png.wid * scale1;
	//int ySize = png.hei * scale1;
	// For each vertex, assign texture coordinate before vertex coordinate.
	glTexCoord2d(0.0, 0.0);   // these are "percentage" of the image
	glVertex3d(30, 0, -0.1);        // these are actual pixel coordinates on screen

	glTexCoord2d(1.0, 0.0);
	glVertex3d(30 + 5, 0, -0.1);

	glTexCoord2d(1.0, 1.0);
	glVertex3d(30 + 5, 0 + 5, -0.1);

	glTexCoord2d(0.0, 1.0);
	glVertex3d(30, 0 + 5, -0.1);
	glEnd();
	for (int i = 0; i<ySize+1; i++) {
		for (int j = 0; j < xSize+1; j++) {
			if (map[i][j] == "1") {
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
				glEnd();
			}
			else if (map[i][j] == "d") {
				glColor3ub(100, 1, 5);
				DrawingUtilNG::drawCube((j - 1) * 20, 0, (i - 1) * 20, j * 20, 20.0, i * 20, false);
			}
			else if (map[i][j] == "e") {
				glColor3ub(255, 0, 0);
				DrawingUtilNG::drawCube((j - 1) * 20 +5, 0, (i - 1) * 20+5, j * 20-5, 10.0, i * 20-5, false);
				glColor3ub(69, 69, 69);
				DrawingUtilNG::drawCube((j - 1) * 20, -1, (i - 1) * 20, j * 20, 0, i * 20, false);
			}
			else {
				glColor3ub(69, 69, 69);
				DrawingUtilNG::drawCube((j - 1) * 20, -1, (i - 1) * 20, j * 20, 0, i * 20, false);
				//DrawingUtilNG::drawCube((j - 1) * 20, 20, (i - 1) * 20, j * 20, 21, i * 20, false);
			}	
		}
	}

}

int main(void)
{
	bool terminate = false;
	Camera3D camera;
	OrbitingViewer orbit;
	vector<vector<string>> viewer;

	//camera.z = 10.0;
	Maze theMaze("testMap.txt");
	theMaze.load();
	FsOpenWindow(16, 16, 1200, 800, 1);

	theMaze.print();
	//initialize special fonts (after FsOpenWindow)
	ComicSansFont comicsans;
	comicsans.setColorHSV(300, 1, 1);
	ImpactFont impact;
	
	//shit here
	YsRawPngDecoder png[2];
	png[0].Decode("wall.png");
	png[1].Decode("wall.png");


	GLuint texId[2];  // this will be use as texture identifiers for the two PNGs

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

	double angle = 0.0;
	int key;
	Entity theEntity(theMaze.getStartX(), theMaze.getStartY(),3);

	while (FSKEY_ESC != (key = FsInkey()))
	{
		FsPollDevice();

		int wid, hei;
		FsGetWindowSize(wid, hei);

		int key = FsInkey();
		switch (key)
		{
		case FSKEY_ESC:
			terminate = true;
			break;
		}
		if (FSKEY_UP <= key && key <= FSKEY_RIGHT) // Task 3
			switch (key) {
			case 67: //up
				switch (theEntity.getDirection()) {
				case 0:
					if (theEntity.moveRight(theMaze)) {
						camera.x += 20;
					}
					break;
				case 1:
					if (theEntity.moveUp(theMaze)) {
						camera.z -= 20;
					}
					break;
				case 2:
					if (theEntity.moveLeft(theMaze)) {
						camera.x -= 20;
					}
					break;
				case 3:
					if (theEntity.moveDown(theMaze)) {
						camera.z += 20;
					}
					break;
				}

				
				break;
			//case 68: //down
			//	if (theEntity.moveDown(theMaze)) {
			//		camera.z += 20;
			//	}
			//	break;
			case 69: //left
				camera.h += Camera3D::PI / 2;
				theEntity.changeDirection(1);
				break;
			case 70: //right
				camera.h -= Camera3D::PI / 2;
				theEntity.changeDirection(0);
				break;
			}


		if (key == FSKEY_A) //attack
		{
			return theEntity.attack(theEntity.getX(), theEntity.getY(), theMaze);
		}

		if (key == FSKEY_S)//consume potion
		{
			return theEntity.drink();
		}

		if (key == FSKEY_D) //item pickup
		{
			if (theMap.checkTile(theEntity.getPosition()) == 'i')
			{
				theEntity.getItem(theMap[theEntity.getPosition()]);
				return false;
			}
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
		
		viewer = theMaze.view(theEntity);
		drawMap(viewer, texId[1],theMaze.getCol(),theMaze.getRow());
		//DrawingUtilNG::drawCube(-10.0, -10.0, -10.0, 10.0, 10.0, 10.0);
		//DrawingUtilNG::drawCube(0, 0, 0, 20.0, 50.0, 20.0, false);
		

		
		// draw axes

		comicsans.drawText3D("  Hello World", { 0,-20,0 }, { 0,10,0 }, { -1,-20,-1 }, .3, 20.);

		// Set up 2D drawing
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, (float)wid - 1, (float)hei - 1, 0, -1, 1);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glDisable(GL_DEPTH_TEST);
		theMaze.draw();
		comicsans.drawText(to_string(camera.x), 10, 40, .25);
		comicsans.drawText(to_string(camera.y), 10, 60, .25);
		comicsans.drawText(to_string(camera.z), 10, 80, .25);

		comicsans.drawText(to_string(camera.h), 400, 40, .25);
		comicsans.drawText(to_string(camera.p), 400, 60, .25);
		comicsans.drawText(to_string(camera.b), 400, 80, .25);
		theEntity.draw();
		FsSwapBuffers();
		FsSleep(10);
	}

	return 0;

}