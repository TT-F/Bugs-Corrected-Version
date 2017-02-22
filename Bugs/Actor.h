#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
GraphObject::Direction randDir();

class Actor : public GraphObject
{
public:
	Actor(int ID, int sX, int sY, Direction sDire, int depth, int heSt, bool block, bool move, StudentWorld* world)
		: GraphObject(ID, sX, sY, sDire, depth), Health(heSt), m_world(world), blocked(block), moved(move)
	{};
	virtual ~Actor() {};
	//mutator
	virtual void doSomething() = 0; //pure virtual function, since something can move other things cannot 
	virtual void setHelath(int wantedHealth); //changing the healthy statue of the actor 
	void setmoved(bool input);
	//accesory 
	int randDis(int s, int end);
	bool isblocked() const;
	int currHealth() const;
	StudentWorld* getStdW() const;
	bool ismoved() const;
	//int whatamI() const;

private:
	int Health;
	StudentWorld* m_world;
	bool moved;
	bool blocked;
	
	//int ID;

};

//pebble class 
class pebble : public Actor
{
public:
	pebble(int ID, int sX, int sY, Direction sDire, int depth, int heSt, bool block, StudentWorld* StWorld) :
		Actor(ID, sX, sY, sDire, depth, heSt, block, false, StWorld)
	{};
	virtual void doSomething() {};
private:

};

//baby grass hopper 
class babbyGrasshopper : public Actor //maybe change the base class to Grasshopper will be better 
{
public:
	babbyGrasshopper(int ID, int sX, int sY, Direction sDire, int depth, int heSt, bool block, bool move, StudentWorld* StWorld) :
		Actor(ID, sX, sY, sDire, depth, heSt, block, move, StWorld)
	{};
	virtual void doSomething();

	//Mutator 
	void setdisDistance(int input);
	
	//Accessory 
	int getdisDistance() const;
	
private:
	int disredDistance;
	
	GraphObject::Direction disDir;
};

struct Cord
{
	int X;
	int Y;
};



#endif // ACTOR_H_
