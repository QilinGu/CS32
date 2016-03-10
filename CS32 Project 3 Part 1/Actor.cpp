#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

//////////////////////////
//ACTOR IMPLEMENTATIONS///
//////////////////////////

Actor::Actor(int imageID, int startX, int startY, Direction startDirection, StudentWorld* studentWorld, int hitpoints)
	: GraphObject(imageID, startX, startY, startDirection)
{
	m_ID = imageID;
	m_studentWorld = studentWorld;
	m_alive = true;
	m_hitpoints = hitpoints;
}

int Actor::getID() const
{
	return m_ID;
}

bool Actor::getAlive() const
{
	return m_alive;
}

void Actor::setAlive(bool status)
{
	m_alive = status;
}

StudentWorld* Actor::getWorld() const
{
	return m_studentWorld;
}

//////////////////////////
//PLAYER IMPLEMENTATIONS//
//////////////////////////

Player::Player(int startX, int startY, StudentWorld* studentWorld, int imageID, Direction startDirection, int hitpoints, int ammo)
	: Actor(imageID, startX, startY, startDirection, studentWorld, hitpoints)
{
	setVisible(true);
	m_ammo = ammo;
}

void Player::doSomething()
{
	if (!getAlive())
		return;

	int ch;
	if (getWorld()->getKey(ch))
	{
		switch (ch)
		{
		case KEY_PRESS_UP:
			setDirection(up);
			if (getWorld()->canPlayerMoveThere(getX(), getY() + 1, KEY_PRESS_UP))
				moveTo(getX(), getY() + 1);
			break;
		case KEY_PRESS_DOWN:
			setDirection(down);
			if (getWorld()->canPlayerMoveThere(getX(), getY() - 1, KEY_PRESS_DOWN))
				moveTo(getX(), getY() - 1);
			break;
		case KEY_PRESS_LEFT:
			setDirection(left);
			if (getWorld()->canPlayerMoveThere(getX() - 1, getY(), KEY_PRESS_LEFT))
				moveTo(getX() - 1, getY());
			break;
		case KEY_PRESS_RIGHT:
			setDirection(right);
			if (getWorld()->canPlayerMoveThere(getX() + 1, getY(), KEY_PRESS_RIGHT))
				moveTo(getX() + 1, getY());
			break;
		case KEY_PRESS_SPACE:
			if (m_ammo != 0)
				m_ammo--;
			break;
		case KEY_PRESS_ESCAPE:
			setAlive(false);
			break;
		}
	}
}

bool Player::checkIfPlayerIsOnExit()
{
	return false;
}

//////////////////////////
//WALL IMPLEMENTATIONS////
//////////////////////////

Wall::Wall(int startX, int startY, StudentWorld* studentWorld, int imageID, Direction startDirection, int hitpoints)
	: Actor(imageID, startX, startY, startDirection, studentWorld, hitpoints)
{
	setVisible(true);
}

void Wall::doSomething() {}

//////////////////////////
//EXIT IMPLEMENTATIONS////
//////////////////////////

Exit::Exit(int startX, int startY, StudentWorld* studentWorld, int imageID, Direction startDirection, int hitpoints)
	: Actor(imageID, startX, startY, startDirection, studentWorld, hitpoints)
{
	setVisible(false);
}

void Exit::doSomething() {}

///////////////////////////
//BOULDER IMPLEMENTATIONS//
///////////////////////////

Boulder::Boulder(int startX, int startY, StudentWorld* studentWorld, int imageID, Direction startDirection, int hitpoints)
	: Actor(imageID, startX, startY, startDirection, studentWorld, hitpoints)
{
	setVisible(true);
}

void Boulder::doSomething() {}

//////////////////////////
//HOLE IMPLEMENTATIONS////
//////////////////////////

Hole::Hole(int startX, int startY, StudentWorld* studentWorld, int imageID, Direction startDirection, int hitpoints)
	: Actor(imageID, startX, startY, startDirection, studentWorld, hitpoints)
{
	setVisible(true);
}

void Hole::doSomething()
{
	if (!getAlive())
		return;

	if (getWorld()->isBoulderOnHole(getX(), getY()))
		setAlive(false);
}

//////////////////////////
//JEWEL IMPLEMENTATIONS///
//////////////////////////

Jewel::Jewel(int startX, int startY, StudentWorld* studentWorld, int imageID, Direction startDirection, int hitpoints)
	: Actor(imageID, startX, startY, startDirection, studentWorld, hitpoints)
{
	setVisible(true);
}

void Jewel::doSomething()
{
	if (!getAlive())
		return;

	if (getWorld()->isPlayerOnJewel(getX(), getY()))
	{
		getWorld()->increaseScore(50);
		setAlive(false);
	}
}

