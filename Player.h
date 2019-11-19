#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include "fssimplewindow.h"

using namespace std;


class Player {
protected:
	int health;
	int xpos, ypos;
	bool holdingWeapon;
	bool holdingPotion;
	int dir;

public:
	Player(int xstart, int ystart)
		//function names here
	void move(int d);
	void attack(int x, int y);
	void drink();
	void pickUp(int x, int y);
	void loseHp(int x);
};