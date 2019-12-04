#include "Entity.h"
#include "Maze.h"
#include "fssimplewindow.h"
#include "Enemy.h"
#include <algorithm>
#include <iostream>
using namespace std;
class Maze;
class Enemy;

void Entity::draw()
{
	glColor3ub(0, 0, 255);
	int yp = 4;
	int xp = 4;
	glBegin(GL_QUADS);
	glVertex2i(yp * 20 - 5, xp * 20 - 5);
	glVertex2i(yp * 20 - 15, xp * 20 - 5);
	glVertex2i(yp * 20 - 15, xp * 20 - 15);
	glVertex2i(yp * 20 - 5, xp * 20 - 15);
	glEnd();
	glColor3ub(255, 212, 148);
	switch (direction) {
	case 0:
		glBegin(GL_TRIANGLES);
		glVertex2i(yp * 20 - 10, xp * 20 - 10);
		glVertex2i(yp * 20 + 5, xp * 20 - 5);
		glVertex2i(yp * 20 + 5, xp * 20 - 15);
		glEnd();
		break;
	case 1:
		glBegin(GL_TRIANGLES);
		glVertex2i(yp * 20 - 10, xp * 20 - 10);
		glVertex2i(yp * 20 - 5, xp * 20 - 25);
		glVertex2i(yp * 20 - 15, xp * 20 - 25);
		glEnd();
		break;
	case 2:
		glBegin(GL_TRIANGLES);
		glVertex2i(yp * 20 - 10, xp * 20 - 10);
		glVertex2i(yp * 20 - 25, xp * 20 - 5);
		glVertex2i(yp * 20 - 25, xp * 20 - 15);
		glEnd();
		break;
	case 3:
		glBegin(GL_TRIANGLES);
		glVertex2i(yp * 20 - 10, xp * 20 - 10);
		glVertex2i(yp * 20 - 5, xp * 20 + 5);
		glVertex2i(yp * 20 - 15, xp * 20 + 5);
		glEnd();
		break;
	}
	
}

bool Entity::checkBelow(Maze& aMaze)
{
	if (aMaze.getMap(xPos, yPos) == "p" || aMaze.getMap(xPos, yPos) == "w" || aMaze.getMap(xPos, yPos) == "p" || aMaze.getMap(xPos, yPos) == "k")
	{
		return true;
	}
	return false;
}

bool Entity::moveUp(Maze& aMaze)
{
	string myArray[] = { "0","p","w"};
	size_t myArraySize = sizeof(myArray) / sizeof(int);
	string* end = myArray + myArraySize;
	// find the value 0:
	
	if (xPos > 1) {
		//string* result = std::find(myArray, end, aMaze.getMap(xPos - 1, yPos));
		if (aMaze.getMap(xPos - 1, yPos)!="e"&& aMaze.getMap(xPos - 1, yPos)!="1"&& aMaze.getMap(xPos - 1, yPos)!="d") {
			xPos--;
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

bool Entity::moveDown(Maze& aMaze)
{
	string myArray[] = { "0","p","w" ,"k"};
	size_t myArraySize = sizeof(myArray) / sizeof(int);
	string* end = myArray + myArraySize;
	// find the value 0:
	if (xPos < aMaze.getRow()){
		string* result = std::find(myArray, end, aMaze.getMap(xPos + 1, yPos));
		if (result != end) {
			xPos++;
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

bool Entity::moveLeft(Maze& aMaze)
{
	if (aMaze.getMap(xPos, yPos-1) != "e" && aMaze.getMap(xPos, yPos-1) != "1" && aMaze.getMap(xPos, yPos-1) != "d") {
		yPos--;
		return true;
	}
	else {
		return false;
	}
}

void Entity::setDirection(int dir) {
	direction = dir;
}

bool Entity::moveRight(Maze& aMaze)
{
	if (yPos < aMaze.getCol() && aMaze.getMap(xPos, yPos + 1) != "e" && aMaze.getMap(xPos, yPos + 1) != "1" && aMaze.getMap(xPos, yPos + 1) != "d") {
		yPos++;
		return true;
	}
	else {
		return false;
	}
}

bool Entity::reachedGoal(Maze& aMaze)
{
	if (xPos == aMaze.getEndX() && yPos == aMaze.getEndY()) {

		return 1;
	}
	return 0;
}


void Entity::changeDirection(bool dir)
{
	//bool = 1 for left 
	if (dir) {
		direction += 1;
		if (direction == 4) {
			direction = 0;
		}
	}
	//bool = 0 for right
	else {
		direction -= 1;
		if (direction == -1) {
			direction = 3;
		}
	}
}



bool Entity::attack(int x, int y, Maze& aMaze, Enemy& anEnemy) {
	//if spot ahead has enemy
	int dir = this->direction; //0 for right, go counterclockwise
	if (dir == 0) {
		y += 1;
	}
	else if (dir == 1) {
		x -= 1;
	}
	else if (dir == 2) {
		y -= 1;
	}
	else if (dir == 3) {
		x += 1;
	}
	if (x == anEnemy.getX() && y == anEnemy.getY() && anEnemy.isLiving()) {
		//potentially make enemy at that location flash to show attack
		//enemy at that location loses x hp
		anEnemy.damage(attackNum);
		if (anEnemy.getHealth() <= 0) {
			anEnemy.die(aMaze);
		}
		return true;
	}

	else {
		return false;
	}
}


bool Entity::drink() {
	if (holdingPotion>0) {
		health += 50; //how much hp to add?
		holdingPotion -= 1;
		return true;
	}
	else {
		return false;
	}
}

int Entity::pickUp(int x, int y, Maze& aMaze) {
	if (aMaze.getMap(x,y) == "p") {
		//remove potion from map
		aMaze.replace(x, y, "0");
		holdingPotion +=1;
		return 0;
	}
	else if (aMaze.getMap(x,y) == "w") {
		//remove weapon from map
		attackNum +=2;
		aMaze.replace(x, y, "0");
		return 1;
	}
	else if (aMaze.getMap(x, y) == "k") {
		//remove weapon from map
		holdingKey = true;
		aMaze.replace(x, y, "0");
		return 3;
	}
	else {
		return 2;
	}
}

void Entity::loseHp(int x) {
	health -= x;
}


