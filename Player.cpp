
#include <fstream>
#include <iostream>
#include <string>
#include "fssimplewindow.h"

using namespace std;

//int health;
//int xpos, ypos;
//bool holdingWeapon;
//int dir;

const int MAP_SIZE; //change these
const int MAX_HP;

Player::Player(int xstart, int ystart) {
	xpos = xstart; 
	ypos = ystart;
	holdingPotion = false;
	holdingWeapon = false;
	hp = MAX_HP;
	dir = 1; 
}

//1 forward, 2 left, 3 right, 4 back
void Player::move(int d) {
	if (d == 1 && ypos > 0 && map[xpos][ypos-1] != 1) {
		ypos--;
	}
	else if (d == 2 && xpos > 0 && map[xpos-1][ypos] != 1) {
		xpos--;
	}
	else if (d == 3 && xpos < MAP_SIZE - 1 && map[xpos+1][ypos] != 1) {
		xpos++;
	}
	else if (d == 4 && ypos < MAP_SIZE - 1 && map[xpos][ypos+1] != 1) {
		ypos++;
	}
	else {
		//throw error
	}
}

void Player::attack(int x, int y) {
	//if spot ahead has enemy
	if (map[x][y] == 'e') {
		//potentially make enemy at that location flash to show attack
		//enemy at that location loses x hp
	}

	else {
		cout << "How anticlimactic. You lash out in front of you but there's nothing there..." << endl;
	}
}

void Player::drink() {
	if (holdingPotion) {
		player.hp += 10; //how much hp to add?
		holdingPotion = false;
		cout << "You chug some drink. You feel 10HP healthier." << endl;
	}
	else {
		cout << "You feel parched but have nothing to sate your thirst." << endl;
	}
}

void Player::pickUp(int x, int y) {
	if (map[x][y] == 'p') {
		//remove potion from map
		holdingPotion = true;
		cout << "You pick up a bottle of some kind of liquid." << endl;
	}
	else if (map[x][y] == 'w') {
		//remove weapon from map
		holdingWeapon = true;
		cout << "You pick up something sharp and pointy. Looks like it could make for a good weapon." << endl;
	}
	else {
		cout << "You bend down only to realize there's nothing for you to pick up. You tie your shoe instead." << endl;
	}
}

void Player::loseHp(int x){
	hp -= x;
}


