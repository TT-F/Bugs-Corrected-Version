#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include <string>
#include <list>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp
class Actor;
class field;
class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir)
		: GameWorld(assetDir)
	{
	}

	virtual ~StudentWorld();

	virtual int init();

	virtual int move();

	virtual void cleanUp();

	bool checkpebble(int x, int y);

	void updateTickCount();


	void resetmoved();

private:
	std::list<Actor*> actorobjhld[VIEW_WIDTH][VIEW_HEIGHT];
	int elaptick = 0;

};



#endif // STUDENTWORLD_H_
