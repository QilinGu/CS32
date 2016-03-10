#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include "Level.h"
#include <string>
#include <vector>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir)
		: GameWorld(assetDir) {}

	virtual int init();

	virtual int move();

	virtual void cleanUp();

	bool canPlayerMoveThere(int x, int y, int moveDirection);

	bool canBouldersMoveThere(int x, int y);

	bool isBoulderOnHole(int x, int y);

	bool isPlayerOnJewel(int x, int y);

	~StudentWorld();

private:
	std::vector<Actor*> m_actorVector;
	Player* m_player;	

	int getWhatIsAt(int x, int y); // returns ID
};

#endif // STUDENTWORLD_H_
