#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"
#include "Compiler.h"

//Notes========================================
// remeber to add virtual destructor 
//=============================================

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
		: GraphObject(ID, sX, sY, sDire, depth), Health(heSt), m_world(world), blocked(block), moved(move), alive(true), ID(ID), sx(sX), sy(sY), selfID(false), isStun(false), isPosion(false), isbitten(false)
	{};
	virtual ~Actor() {};
	
	virtual void doSomething() = 0; //pure virtual function, since something can move other things cannot 
	virtual void setHelath(int wantedHealth); //changing the healthy statue of the actor 
	void setmoved(bool input);
	void setalive(bool input);
	void setX(int input);
	void setY(int input);
	void initselfID() { selfID = true; };
	void removeselfID() { selfID = false; };
	void setColN(int input) { colNum = input; };
	bool getselfID() { return selfID; };
	Actor* bite(int x, int y, int lost);
	void setStun(int input);
	void letStun(bool input);
	void letPoison(bool input);
	bool istStun() const { return isStun; };
	bool istPosion() const { return isPosion; };
	bool checksleeping();
	int randDis(int s, int end);
	bool isblocked() const;
	int currHealth() const;
	StudentWorld* getStdW() const;
	bool ismoved() const;
	bool getalive() const;
	int whatamI() const;
	int getStun() const;
	int getColN() const { return colNum; };
	void setisbitten(bool input) { isbitten = input; };
	bool getisbitten() { return isbitten; };
	

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
	int Stun;
	int colNum;
	bool isStun;
	bool isPosion;
	bool isbitten;
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
		Actor(ID, sX, sY, sDire, depth, heSt, block, move, StWorld)
	{
		
	};
	virtual void doSomething()=0;
	//utility 
	
	bool checkhealth(); 
	
	bool eatfood();
	bool randomsleep();
	bool move();
	void checkandwalk();
	void setdisDir(GraphObject::Direction input) { disDir = input; };
	GraphObject::Direction getdisDir() { return disDir; };
	Cord radiusten();
	
	

	//Mutator 
	void setdisDistance(int input);
	
	void bitother(int ID, int x, int y, int input);
	

	//Accessory 
	int getdisDistance() const;
	
private:
	int disredDistance;
	GraphObject::Direction disDir;
	
	
};

//============================================================
//=                  babbygrasshopper class                  =
//============================================================
class babbyGrasshopper : public insects //maybe change the base class to Grasshopper will be better 
{
public:
	babbyGrasshopper(int ID, int sX, int sY, Direction sDire, int depth, int heSt, bool block, bool move, StudentWorld* StWorld) :
		 insects(ID, sX, sY, sDire, depth, heSt, block, move, StWorld)
	{
		setStun(2);
	};
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
		insects(IID_ADULT_GRASSHOPPER, sX, sY, randDir(), 0, 1600, false, false, StWorld) {
		setStun(2);
	};
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

//============================================================
//=                  trap class                              =
//============================================================
class trap : public Actor
{
public: 
	trap(int ID, int sX, int sY, StudentWorld* StWorld) :
		Actor(ID, sX, sY, GraphObject::right, 2, 10000, false, false, StWorld)
	{};
	virtual void doSomething() {};
	
private:
};

//============================================================
//=                  poison class                            =
//============================================================
class poison :public trap
{
public:
	poison(int sX, int sY, StudentWorld* stw) :
		trap(IID_POISON, sX, sY, stw)
	{};
	virtual void doSomething();
};

//============================================================
//=                  Pool of water class                     =
//============================================================
class poolofWater : public trap
{
public:
	poolofWater(int sX, int sY, StudentWorld* stw) :
		trap(IID_WATER_POOL, sX, sY, stw)
	{};
	virtual void doSomething();

};

//============================================================
//=                 Pheromone class                          =
//============================================================
class pheromone : public Actor
{
public:
	pheromone(int ID, int sx, int sy, StudentWorld* stw):
		Actor(ID, sx, sy, GraphObject::right, 2,256,false,false,stw )
	{};
	virtual void doSomething();
};

//============================================================
//=                     Ant   class                          =
//============================================================
class Ant : public insects
{
public:
	Ant(int ID, int colN, int sx, int sy, Compiler* compiler, StudentWorld*stw) :
		insects(ID, sx, sy, randDir(), 1, 1500, false, false, stw),  m_compiler(compiler), isblocked(false)
	{
		setColN(colN);
	};
	virtual void doSomething();
	//int getColN() { return colNum; };
	void setisblocked(bool input) { isblocked = input; };
	
	bool getisblocked() { return isblocked; };
	void setfoodholder(int input) { foodholder += input; };
	int getfoodholder() { return foodholder; };

private:
	//int colNum;
	Compiler* m_compiler;
	int ic = 0; //instruction counter (what does it do????)
	bool isblocked;
	
	int foodholder = 0;
	int randNumber;
};

//============================================================
//=                   Anthill class                          =
//============================================================
class Anthill : public Actor //need passing in a Compiler Object 
{
public:
	Anthill(int sx, int sy, int ColN, Compiler* compiler, StudentWorld* stw) : Actor(IID_ANT_HILL, sx, sy, GraphObject::right, 2, 8999, false, false, stw), m_compiler(compiler)
	{
		setColN(ColN);
	};
	virtual void doSomething();
	
	Compiler* getComp() { return m_compiler; };

private:
	
	Compiler* m_compiler;
};


#endif // ACTOR_H_
