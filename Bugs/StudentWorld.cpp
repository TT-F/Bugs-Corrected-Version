#include "StudentWorld.h"
#include "Actor.h"
#include "Field.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp


StudentWorld:: ~StudentWorld()
{
	cleanUp();
}


int StudentWorld::init()
{

	//loading field 
	Field f;
	//string fieldFile = getFieldFilename();???????????????????????
	string fieldFile = "field.txt";
	string error;
	if (f.loadField(fieldFile, error) != Field::LoadResult::load_success)
	{
		setError(fieldFile + " " + error);
		return GWSTATUS_LEVEL_ERROR; // something bad happened!
	}

	//otherwise 
	//creating objects 
	for (int x = 0; x < 64;x++)
	{
		for (int y = 0; y < 64; y++)
		{
			Field::FieldItem item = f.getContentsOf(x, y); // note it’s x,y and not y,x!!!
			if (item == Field::FieldItem::rock)
			{
				Actor* Ptr = new pebble(IID_ROCK, x, y, GraphObject::right, 1, 100000, this);
				actorobjhld.push_front(Ptr);
			}
			else if (item == Field::FieldItem::grasshopper)
			{
				Actor* Ptr = new babbyGrasshopper(IID_BABY_GRASSHOPPER, x, y, randDir(), 0, 500, this); //direction random IS THE POINTER USED CORRECTLY??
				actorobjhld.push_front(Ptr);
			}
			//more if statements required to be implemented 
		}
	}
	return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
	//increase ticks 
	updateTickCount();
	// responsible for asking each of the simulation’s actor objects
	//(e.g., each of the ants, grasshoppers, pheromones, etc.) to try to do something
	for (std::list<Actor*>::iterator ite = actorobjhld.begin(); ite != actorobjhld.end(); ++ite)
	{
		(*ite)->doSomething();
	}

	//responsible for disposing of(i.e., deleting) Actor that need to disappear during a given tick

	//update status 

	return 0;
}

void StudentWorld::cleanUp()
{
	//freeing all Actor
	for (std::list<Actor*>::iterator ite = actorobjhld.begin(); ite != actorobjhld.end(); ++ite)
	{
		delete *ite;
	}
}

Actor* StudentWorld::find(int x, int y)
{
	for (std::list<Actor*>::iterator ite = actorobjhld.begin(); ite != actorobjhld.end(); ++ite)
	{
		if ((*ite)->getX() == x && (*ite)->getY() == y)
			return *ite;
	}
	return nullptr;
}

void StudentWorld::updateTickCount()
{
	elaptick++;
}
