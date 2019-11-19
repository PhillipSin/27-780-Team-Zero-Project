#include "Entity.h"
#include "Maze.h"
#include "fssimplewindow.h"
#include <iostream>
using namespace std;
class Maze;

void Entity::draw()
{
	glColor3ub(0, 0, 255);
	glBegin(GL_QUADS);
	glVertex2i(yPos * 20 - 5, xPos * 20 - 5);
	glVertex2i(yPos * 20 - 15, xPos * 20 - 5);
	glVertex2i(yPos * 20 - 15, xPos * 20 - 15);
	glVertex2i(yPos * 20 - 5, xPos * 20 - 15);
	glEnd();
	glColor3ub(255, 212, 148);
	switch (direction) {
	case 0:
		glBegin(GL_TRIANGLES);
		glVertex2i(yPos * 20 - 10, xPos * 20 - 10);
		glVertex2i(yPos * 20 + 5, xPos * 20 - 5);
		glVertex2i(yPos * 20 + 5, xPos * 20 - 15);
		glEnd();
		break;
	case 1:
		glBegin(GL_TRIANGLES);
		glVertex2i(yPos * 20 - 10, xPos * 20 - 10);
		glVertex2i(yPos * 20 - 5, xPos * 20 - 25);
		glVertex2i(yPos * 20 - 15, xPos * 20 - 25);
		glEnd();
		break;
	case 2:
		glBegin(GL_TRIANGLES);
		glVertex2i(yPos * 20 - 10, xPos * 20 - 10);
		glVertex2i(yPos * 20 - 25, xPos * 20 - 5);
		glVertex2i(yPos * 20 - 25, xPos * 20 - 15);
		glEnd();
		break;
	case 3:
		glBegin(GL_TRIANGLES);
		glVertex2i(yPos * 20 - 10, xPos * 20 - 10);
		glVertex2i(yPos * 20 - 5, xPos * 20 + 5);
		glVertex2i(yPos * 20 - 15, xPos * 20 + 5);
		glEnd();
		break;
	}
	
}

bool Entity::moveUp(Maze& aMaze)
{

	if (xPos > 1 && aMaze.getMap(xPos - 1, yPos) == "0") {
		xPos--;
		return true;
	}
	else {
		return false;
	}
}

bool Entity::moveDown(Maze& aMaze)
{
	if (xPos < aMaze.getRow() && aMaze.getMap(xPos + 1, yPos) == "0") {
		xPos++;
		return true;
	}
	else {
		return false;
	}
}

bool Entity::moveLeft(Maze& aMaze)
{
	if (yPos > 1 && aMaze.getMap(xPos, yPos - 1) == "0") {
		yPos--;
		return true;
	}
	else {
		return false;
	}
}

bool Entity::moveRight(Maze& aMaze)
{
	if (yPos < aMaze.getCol() && aMaze.getMap(xPos, yPos + 1) == "0") {
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

void Entity::attack(int x, int y, Maze& aMaze) {
	//if spot ahead has enemy
	if (aMaze.getMap(x,y) == "e") {
		//potentially make enemy at that location flash to show attack
		//enemy at that location loses x hp
	}

	else {
		cout << "How anticlimactic. You lash out in front of you but there's nothing there..." << endl;
	}
}

void Entity::drink() {
	if (holdingPotion) {
		health += 10; //how much hp to add?
		holdingPotion = false;
		cout << "You chug some drink. You feel 10HP healthier." << endl;
	}
	else {
		cout << "You feel parched but have nothing to sate your thirst." << endl;
	}
}

void Entity::pickUp(int x, int y, Maze& aMaze) {
	if (aMaze.getMap(x,y) == "p") {
		//remove potion from map
		holdingPotion = true;
		cout << "You pick up a bottle of some kind of liquid." << endl;
	}
	else if (aMaze.getMap(x,y) == "w") {
		//remove weapon from map
		holdingWeapon = true;
		cout << "You pick up something sharp and pointy. Looks like it could make for a good weapon." << endl;
	}
	else {
		cout << "You bend down only to realize there's nothing for you to pick up. You tie your shoe instead." << endl;
	}
}

void Entity::loseHp(int x) {
	health -= x;
}


