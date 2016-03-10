#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"

class StudentWorld;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

//////////////////////////
//ACTOR DECLARATION//////
//////////////////////////

class Actor : public GraphObject
{
public:
	Actor(int imageID, int startX, int startY, Direction startDirection, StudentWorld* studentWorld, int hitpoints);
	virtual void doSomething() = 0;
	int getID() const;
	bool getAlive() const;
	void setAlive(bool status);
	StudentWorld* getWorld() const;

private:
	int m_ID;
	bool m_alive;
	int m_hitpoints;
	StudentWorld* m_studentWorld;	
};

//////////////////////////
//PLAYER DECLARATION/////
//////////////////////////

class Player : public Actor
{
public:
	Player(int startX, int startY, StudentWorld* studentWorld, int imageID = IID_PLAYER, Direction startDirection = right, int hitpoints = 20, int ammo = 20);
	void doSomething();
	bool checkIfPlayerIsOnExit();

private:
	int m_ammo;
}; 

//////////////////////////
//WALL DECLARATION///////
//////////////////////////

class Wall : public Actor
{
public:
	Wall(int startX, int startY, StudentWorld* studentWorld, int imageID = IID_WALL, Direction startDirection = none, int hitpoints = 1);
	void doSomething();

private:
}; 

//////////////////////////
//EXIT DECLARATION///////
//////////////////////////

class Exit : public Actor
{
public:
	Exit(int startX, int startY, StudentWorld* studentWorld, int imageID = IID_EXIT, Direction startDirection = none, int hitpoints = 1);
	void doSomething();

private:
}; 

//////////////////////////
//BOULDER DECLARATION/////
//////////////////////////

class Boulder : public Actor
{
public:
	Boulder(int startX, int startY, StudentWorld* studentWorld, int imageID = IID_BOULDER, Direction startDirection = none, int hitpoints = 1);
	void doSomething();

private:
};

////////////////////////
//HOLE DECLARATION//////
////////////////////////

class Hole : public Actor
{
public:
	Hole(int startX, int startY, StudentWorld* studentWorld, int imageID = IID_HOLE, Direction startDirection = none, int hitpoints = 1);
	void doSomething();

private:
};

////////////////////////
//JEWEL DECLARATION/////
////////////////////////

class Jewel : public Actor
{
public:
	Jewel(int startX, int startY, StudentWorld* studentWorld, int imageID = IID_JEWEL, Direction startDirection = none, int hitpoints = 1);
	void doSomething();

private:
};

//////////////////////////
//BULLET DECLARATION//////
//////////////////////////



#endif // ACTOR_H_
