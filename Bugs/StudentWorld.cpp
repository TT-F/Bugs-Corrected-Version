#include "StudentWorld.h"
#include "Actor.h"
#include "Field.h"
#include <string>
#include <iostream> 
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

	//creating objects 
	for (int x = 0; x < 64;x++)
	{
		for (int y = 0; y < 64; y++)
		{
			Field::FieldItem item = f.getContentsOf(x, y); // note it’s x,y and not y,x!!!
			if (item == Field::FieldItem::rock)
			{
				Actor* Ptr = new pebble(IID_ROCK, x, y, GraphObject::right, 1, 100000, true, this);
				actorobjhld[x][y].push_front(Ptr);
			}
			else if (item == Field::FieldItem::grasshopper)
			{
				Actor* Ptr = new babbyGrasshopper(IID_BABY_GRASSHOPPER, x, y, randDir(), 0, 500, false, false, this); //direction random IS THE POINTER USED CORRECTLY??
				actorobjhld[x][y].push_front(Ptr);
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

	for (int x = 0; x < VIEW_WIDTH;x++)
	{
		for (int y = 0; y < VIEW_HEIGHT;y++)
		{		
				std::list<Actor*>::iterator ite = actorobjhld[x][y].begin();
				while (ite != actorobjhld[x][y].end())
				{

					if (!(*ite)->ismoved())
					{
						(*ite)->doSomething();
						(*ite)->setmoved(true);
						if ((*ite)->getX() != x || (*ite)->getY() != y)
						{
							actorobjhld[(*ite)->getX()][(*ite)->getY()].push_back(*ite);
							ite = actorobjhld[x][y].erase(ite);
						}
						else
							ite++;
					}
					else
						ite++;
				}
		}
	}
	resetmoved();

	//responsible for disposing of(i.e., deleting) Actor that need to disappear during a given tick

	//update status 

	return 0;
}

void StudentWorld::cleanUp()
{
	
	for (int x = 0; x < VIEW_WIDTH;x++)
	{
		for (int y = 0; y < VIEW_HEIGHT;y++)
		{
			//freeing all Actor
			for (std::list<Actor*>::iterator ite = actorobjhld[x][y].begin(); ite != actorobjhld[x][y].end(); ++ite)
			{
				delete *ite;
				ite = actorobjhld[x][y].erase(ite);
			}
		}
	}
}

bool StudentWorld::checkpebble(int x, int y)
{
	for (std::list<Actor*>::iterator it = actorobjhld[x][y].begin(); it != actorobjhld[x][y].end(); ++it)
	{
		if ((*it)->isblocked())
			return true;
		else
			return false; 
	}
}


void StudentWorld::updateTickCount()
{
	elaptick++;
}

void StudentWorld::resetmoved()
{

	for (int x = 0; x < VIEW_WIDTH;x++)
	{
		for (int y = 0; y < VIEW_HEIGHT;y++)
		{
			for (std::list<Actor*>::iterator ite = actorobjhld[x][y].begin(); ite != actorobjhld[x][y].end(); ++ite)
			{
				(*ite)->setmoved(false);
			}
		}
	}
}


