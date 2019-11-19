#include <fstream>
#include <iostream>
#include <string>
#include "Enemy.h"
#include "maze.h"
#include "entity.h"
#include "fssimplewindow.h"

class Entity;
class Maze;
using namespace std;

//int health;
//int xPos, yPos;
//bool holdingWeapon;
//int dir;

const int MAP_SIZE = 100; //figure out these constants
const int MAX_HP = 20;
const int ATTACK_POWER = 5;

//1 forward, 2 left, 3 right, 4 back
void Enemy::move(int d, Maze& aMaze) {
	if (d == 1 && yPos > 0 && aMaze.getMap(xPos,yPos-1)!= "1") {
		yPos=yPos-1;
	}
	else if (d == 2 && yPos > 0 && aMaze.getMap(xPos-1,yPos)!= "1") {
		xPos= xPos-1;
	}
	else if (d == 3 && xPos < MAP_SIZE - 1 && aMaze.getMap(xPos+1,yPos) != "1") {
		xPos++;
	}
	else if (d == 4 && yPos < MAP_SIZE - 1 && aMaze.getMap(xPos,yPos+1) != "1") {
		yPos++;
	}
	else {
		cout << "What are you doing? You can't move there." << endl;
	}
}

void Enemy::attack(Entity& anEntity) {
	//allow it to reference player
	anEntity.loseHp(ATTACK_POWER);

}