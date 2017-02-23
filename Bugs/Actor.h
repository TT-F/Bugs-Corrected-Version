#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"

//============================================================
//=                      utility                             =
//============================================================
GraphObject::Direction randDir();
struct Cord
{
	int X;
	int Y;
};

//============================================================
//=                      base class                          =
//============================================================


class Actor : public GraphObject
{
public:
	Actor(int ID, int sX, int sY, Direction sDire, int depth, int heSt, bool block, bool move, StudentWorld* world)
		: GraphObject(ID, sX, sY, sDire, depth), Health(heSt), m_world(world), blocked(block), moved(move), alive(true), ID(ID), sx(sX), sy(sY), selfID(false)
	{};
	virtual ~Actor() {};
	//mutator
	virtual void doSomething() = 0; //pure virtual function, since something can move other things cannot 
	virtual void setHelath(int wantedHealth); //changing the healthy statue of the actor 
	void setmoved(bool input);
	void setalive(bool input);
	void setX(int input);
	void setY(int input);
	void initselfID() { selfID = true; };
	void removeselfID() { selfID = false; };
	bool getselfID() { return selfID; };

	//accesory 
	int randDis(int s, int end);
	bool isblocked() const;
	int currHealth() const;
	StudentWorld* getStdW() const;
	bool ismoved() const;
	bool getalive() const;
	int whatamI() const;

private:
	int Health;
	StudentWorld* m_world;
	bool selfID;
	bool moved;
	bool blocked;
	bool alive;
	int ID;
	int sx;
	int sy;
};

//============================================================
//=                     pebble class                         =
//============================================================
class pebble : public Actor
{
public:
	pebble(int ID, int sX, int sY, Direction sDire, int depth, int heSt, bool block, StudentWorld* StWorld) :
		Actor(ID, sX, sY, sDire, depth, heSt, block, false, StWorld)
	{};
	virtual void doSomething() {};
private:

};
//============================================================
//=                      insects class                       =
//============================================================
class insects :public Actor
{
public:
	insects(int ID, int sX, int sY, Direction sDire, int depth, int heSt, bool block, bool move, StudentWorld* StWorld) :
		Actor(ID, sX, sY, sDire, depth, heSt, block, move, StWorld), Stun(2)
	{};
	virtual void doSomething()=0;
	//utility 
	
	bool checkhealth(); 
	bool checksleeping();
	bool eatfood();
	bool randomsleep();
	void checkandwalk();
	
	
	//Mutator 
	void setdisDistance(int input);
	void setStun(int input);
	void bitother(int ID, int x, int y, int input);
	

	//Accessory 
	int getdisDistance() const;
	int getStun() const;
private:
	int disredDistance;
	GraphObject::Direction disDir;
	int Stun;
	
};

//============================================================
//=                  babbygrasshopper class                  =
//============================================================
class babbyGrasshopper : public insects //maybe change the base class to Grasshopper will be better 
{
public:
	babbyGrasshopper(int ID, int sX, int sY, Direction sDire, int depth, int heSt, bool block, bool move, StudentWorld* StWorld) :
		 insects(ID, sX, sY, sDire, depth, heSt, block, move, StWorld)
	{};
	virtual void doSomething();

private:
	
};
//============================================================
//=                 addultgrasshopper class                  =
//============================================================
class adultGrasshopper : public insects
{
public:
	adultGrasshopper(int sX, int sY, StudentWorld* StWorld) :
		insects(IID_ADULT_GRASSHOPPER, sX, sY, randDir(), 0, 1600, false, false, StWorld) {};
	virtual void doSomething(); 
private:
};

//============================================================
//=                  food class                              =
//============================================================
class food : public Actor
{
public:
	food(int ID, int sX, int sY, int heSt, StudentWorld* StWorld) :
		Actor(ID, sX, sY, GraphObject::right, 2, heSt, false, false, StWorld)
	{};
	virtual void doSomething() {};
	
};





#endif // ACTOR_H_
