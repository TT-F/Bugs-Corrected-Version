#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
GraphObject::Direction randDir();

class Actor : public GraphObject
{
public:
	Actor(int imageID, int startX, int startY, Direction startDirection, int depth, int healthstatue, bool block, StudentWorld* world)
		: GraphObject(imageID, startX, startY, startDirection, depth), Health(healthstatue), m_world(world), blocked(block)
	{};
	//virtual ~Actor();
	//mutator
	virtual void doSomething() = 0; //pure virtual function, since something can move other things cannot 
	virtual void setHelath(int wantedHealth); //changing the healthy statue of the actor 

											  //accesory 
	int randDis(int start, int end);
	bool isblocked() const;
	int currHealth() const;
	StudentWorld* getStdW() const;
	//int whatamI() const;

private:
	int Health;
	StudentWorld* m_world;
	bool blocked;
	//int ID;

};

//pebble class 
class pebble : public Actor
{
public:
	pebble(int imageID, int startX, int startY, Direction startDirection, int depth, int healthstatue, bool block, StudentWorld* StWorld) :
		Actor(imageID, startX, startY, startDirection, depth, healthstatue, block, StWorld)
	{};
	virtual void doSomething() {};
private:

};

//baby grass hopper 
class babbyGrasshopper : public Actor //maybe change the base class to Grasshopper will be better 
{
public:
	babbyGrasshopper(int imageID, int startX, int startY, Direction startDirection, int depth, int healthstatue, bool block, StudentWorld* StWorld) :
		Actor(imageID, startX, startY, startDirection, depth, healthstatue, block, StWorld)
	{};
	virtual void doSomething();
private:
	bool checkSurr(int x, int y, int ox, int oy);
};

struct Cord
{
	int X;
	int Y;
};

bool inbound(int x, int y);

#endif // ACTOR_H_
