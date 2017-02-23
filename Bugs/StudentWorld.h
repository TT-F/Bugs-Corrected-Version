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

	bool checkpebble(int x, int y);  //can be replaced by the findwhatsthere function 

	bool findwhatsthere(int x, int y, int ID);

	void updateTickCount();

	void setDisplayText();

	void resetmoved();

	void addFood(int x, int y, int health);

	void addActor(int x, int y, Actor* actor);
	
	int getCurrentTicks() const;

	bool isthereathingcanbebitten(int x, int y);

	Actor* actor(int x, int y, int ID);

	Actor* aRandthingcanbebitten(int x, int y);

	std::string displayFouritem(int ticks, int a0, int a1, int a2, int a3, int wa);

private:
	std::list<Actor*> actorobjhld[VIEW_WIDTH][VIEW_HEIGHT];
	int elaptick = 0;

};



#endif // STUDENTWORLD_H_
