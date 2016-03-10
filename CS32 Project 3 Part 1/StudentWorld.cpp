#include "StudentWorld.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp

int StudentWorld::getWhatIsAt(int x, int y)
{
	for (int i = 0; i < m_actorVector.size(); i++)
	{
		if (m_actorVector[i]->getX() == x && m_actorVector[i]->getY() == y)
			return m_actorVector[i]->getID();
	}
}

bool StudentWorld::canPlayerMoveThere(int x, int y, int moveDirection)
{
	for (int i = 0; i < m_actorVector.size(); i++)
	{
		if (m_actorVector[i]->getX() == x && m_actorVector[i]->getY() == y)
		{
			switch (m_actorVector[i]->getID())
			{
			case IID_WALL:
			case IID_HOLE:
			case IID_ROBOT_FACTORY:
			case IID_SNARLBOT:
			case IID_KLEPTOBOT:
			case IID_ANGRY_KLEPTOBOT:
				return false;
				break;
			case IID_BOULDER:
				switch (moveDirection)
				{
				case KEY_PRESS_UP:
					if (canBouldersMoveThere(x, y + 1))
					{
						m_actorVector[i]->moveTo(x, y + 1);
						return true;
					}
					else
						return false;
					break;
				case KEY_PRESS_DOWN:
					if (canBouldersMoveThere(x, y - 1))
					{
						m_actorVector[i]->moveTo(x, y - 1);
						return true;
					}
					else
						return false;
					break;
				case KEY_PRESS_LEFT:
					if (canBouldersMoveThere(x - 1, y))
					{
						m_actorVector[i]->moveTo(x - 1, y);
						return true;
					}
					else
						return false;
					break;
				case KEY_PRESS_RIGHT:
					if (canBouldersMoveThere(x + 1, y))
					{
						m_actorVector[i]->moveTo(x + 1, y);
						return true;
					}
					else
						return false;
					break;
				}
			}
		}
	}
	return true;
}

bool StudentWorld::canBouldersMoveThere(int x, int y)
{
	for (int i = 0; i < m_actorVector.size(); i++)
	{
		if (m_actorVector[i]->getX() == x && m_actorVector[i]->getY() == y)
		{
			switch (m_actorVector[i]->getID())
			{
			case IID_WALL:
			case IID_ROBOT_FACTORY:
			case IID_SNARLBOT:
			case IID_KLEPTOBOT:
			case IID_ANGRY_KLEPTOBOT:
			case IID_BOULDER:
			case IID_AMMO:
			case IID_EXTRA_LIFE:
			case IID_RESTORE_HEALTH:
			case IID_EXIT:
			case IID_JEWEL:
				return false;
				break;
			}
		}
	}
	return true;
}

bool StudentWorld::isBoulderOnHole(int x, int y)
{
	for (int i = 0; i < m_actorVector.size(); i++)
	{
		if (m_actorVector[i]->getX() == x && m_actorVector[i]->getY() == y && m_actorVector[i]->getID() == IID_BOULDER)
		{
			m_actorVector[i]->setAlive(false);
			return true;
		}
	}
	return false;
}

bool StudentWorld::isPlayerOnJewel(int x, int y)
{
	if (m_player->getX() == x && m_player->getY() == y)
		return true;
	else 
		return false;
}

int StudentWorld::init()
{
	Level lev(assetDirectory());

	/*unsigned int levelNumber = getLevel();
	string s_levelNumber = "0";
	string levelName = "level" + dat"*/

	Level::LoadResult result = lev.loadLevel("level00.dat");
	if (result == Level::load_fail_file_not_found)
		return GWSTATUS_PLAYER_WON;
	else if (result == Level::load_fail_bad_format)
		return GWSTATUS_LEVEL_ERROR;
	else if (result == Level::load_success)
	{
		for (int x = 0; x < VIEW_WIDTH; x++)
		{
			for (int y = 0; y < VIEW_HEIGHT; y++)
			{
				Level::MazeEntry ge = lev.getContentsOf(x, y); // coordinates
				switch (ge)
				{
				case Level::empty:
					break;
				case Level::exit:
					m_actorVector.push_back(new Exit(x, y, this));
					break;
				case Level::player:
					m_player = new Player(x, y, this);
					break;
					/*case Level::horiz_snarlbot:
					m_actorVector.push_back(new Hori_Snarlbot);
					break;
					case Level::vert_snarlbot:
					m_actorVector.push_back(new Vert_Snarlbot);
					break;
					case Level::kleptobot_factory:
					m_actorVector.push_back(new Kleptobot_Factory);
					break;
					case Level::angry_kleptobot_factory:
					m_actorVector.push_back(new Angry_Kleptobot_Factory);
					break;*/
				case Level::wall:
					m_actorVector.push_back(new Wall(x, y, this));
					break;
				case Level::boulder:
					m_actorVector.push_back(new Boulder(x, y, this));
					break;
				case Level::hole:
					m_actorVector.push_back(new Hole(x, y, this));
					break;
				case Level::jewel:
					m_actorVector.push_back(new Jewel(x, y, this));
					break;
					/*case Level::restore_health:
					m_actorVector.push_back(new Restore_Health);
					break;
					case Level::extra_life:
					m_actorVector.push_back(new Extra_Life);
					break;
					case Level::ammo:
					m_actorVector.push_back(new Ammo);
					break;*/
				}
			}
		}
	}
	return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
	// Update the Game Status Line
	//updateDisplayText(); // update the score/lives/level text at screen top
	// The term "actors" refers to all robots, the Player, Goodies,
	// Boulders, Jewels, Holes, Bullets, the Exit, etc.
	// Give each actor a chance to do something

	if (m_player->getAlive())
		m_player->doSomething();

	for (int i = 0; i < m_actorVector.size(); i++)
	{
		if (m_actorVector[i]->getAlive())
		{
			// ask each actor to do something (e.g. move)
			m_actorVector[i]->doSomething();

			if (!m_player->getAlive())
				return GWSTATUS_PLAYER_DIED;

			//if (getWhatIsAt(m_player->getX(), m_player->getY()) == IID_EXIT) // note to self: may not work if there is bullet on exit
				//increaseScoreAppropriately();
				//return GWSTATUS_FINISHED_LEVEL;
		}
	}

	// Remove newly-dead actors after each tick

	for (int i = 0; i < m_actorVector.size(); i++)
	{
		std::vector<Actor*>::iterator it = m_actorVector.begin() + i;
		if (m_actorVector[i]->getAlive() == false)
		{
			m_actorVector[i]->setVisible(false);
			delete m_actorVector[i];
			m_actorVector.erase(it);
			i--;
		}
	}// delete dead game objects 


	// Reduce the current bonus for the Level by one
	//reduceLevelBonusByOne();


	// If the player has collected all of the Jewels on the level, then we
	// must expose the Exit so the player can advance to the next level

	bool jewelPresent = false;
	Actor* ptr = nullptr;
	for (int i = 0; i < m_actorVector.size(); i++)
	{
		if (m_actorVector[i]->getID() == IID_JEWEL)
			jewelPresent = true;
		if (m_actorVector[i]->getID() == IID_EXIT)
			ptr = m_actorVector[i];
	}

	if (!jewelPresent && ptr != nullptr)
		ptr->setVisible(true);
	// make the exit Active

	// return the proper result
	if (!m_player->getAlive())
		return GWSTATUS_PLAYER_DIED;

	if (getWhatIsAt(m_player->getX(), m_player->getY()) == IID_EXIT && !jewelPresent)
		//increaseScoreAppropriately();
		return GWSTATUS_FINISHED_LEVEL;

	/*if (m_player->checkIfPlayerIsOnExit())
	{
		//increaseScoreAppropriately();
		return GWSTATUS_FINISHED_LEVEL;
	}*/

	return GWSTATUS_CONTINUE_GAME;

	// the player hasn’t completed the current level and hasn’t died, so
	// continue playing the current level	
}

void StudentWorld::cleanUp()
{
	delete m_player;

	for (int i = 0; i < m_actorVector.size(); i++)
		delete m_actorVector[i];

	m_actorVector.clear();
}

StudentWorld::~StudentWorld()
{
	cleanUp();
}