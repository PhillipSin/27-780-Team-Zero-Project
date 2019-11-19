#include <stdio.h>
#include <math.h>
#include <string>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "Camera3D.h"
#include "GraphicFont.h"

int main(void)
{
	bool terminate = false;
	Camera3D camera;

	camera.z = 10.0;
	camera.y = 5.0;

	FsOpenWindow(16, 16, 800, 600, 1);

	//initialize special fonts (after FsOpenWindow)
	ComicSansFont comicsans;
	comicsans.setColorHSV(0, 1, 1);

	while (!terminate)
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

		// note that key state returns if it pressed
		// and I want to capture simultaneous presses

		if (0 != FsGetKeyState(FSKEY_LEFT))
			camera.h += Camera3D::PI / 180.0;

		if (0 != FsGetKeyState(FSKEY_RIGHT))
			camera.h -= Camera3D::PI / 180.0;

		if (0 != FsGetKeyState(FSKEY_UP))
			camera.p += Camera3D::PI / 180.0;

		if (0 != FsGetKeyState(FSKEY_DOWN))
			camera.p -= Camera3D::PI / 180.0;

		if (0 != FsGetKeyState(FSKEY_F)) {
			double vx, vy, vz;
			camera.getForwardVector(vx, vy, vz);
			camera.x += vx * 0.5;
			camera.y += vy * 0.5;
			camera.z += vz * 0.5;
		}
		if (0 != FsGetKeyState(FSKEY_B)) {
			double vx, vy, vz;
			camera.getForwardVector(vx, vy, vz);
			camera.x -= vx * 0.5;
			camera.y -= vy * 0.5;
			camera.z -= vz * 0.5;
		}

		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		glViewport(0, 0, wid, hei);

		// Set up 3D drawing
		camera.setUpCameraProjection();
		camera.setUpCameraTransformation();

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(1, 1);

		// 3D drawing from here
		glColor3ub(0, 0, 255);

		glBegin(GL_LINES);
		int x;
		for (x = -500; x <= 500; x += 20)
		{
			glVertex3i(x, 0, -500);
			glVertex3i(x, 0, 500);
			glVertex3i(-500, 0, x);
			glVertex3i(500, 0, x);
		}

		glEnd();

		// Set up 2D drawing
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, (float)wid - 1, (float)hei - 1, 0, -1, 1);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glDisable(GL_DEPTH_TEST);

		comicsans.drawText("I'm Flying!", 10, 60, .25);
		std::string data;
		data = "X=" + std::to_string(camera.x) + " Y=" + std::to_string(camera.y);
		comicsans.drawText(data, 650, 60, .15);

		FsSwapBuffers();
		FsSleep(10);
	}

	return 0;

}