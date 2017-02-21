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

	Actor* find(int x, int y);

	void updateTickCount();

private:
	std::list<Actor*> actorobjhld;
	int elaptick = 0;



};

#endif // STUDENTWORLD_H_
