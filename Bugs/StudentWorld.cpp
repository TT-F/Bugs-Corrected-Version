#include "StudentWorld.h"
#include "Actor.h"
#include "Field.h"
//#include <string>
#include <iostream> 
#include <sstream>
#include <iomanip>
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
				Actor* Ptr = new babbyGrasshopper(IID_BABY_GRASSHOPPER, x, y, randDir(), 0, 500, false, false, this); 
				actorobjhld[x][y].push_front(Ptr);
			}
			else if (item == Field::FieldItem::food)
			{
				addFood(x, y, 6000);
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
	for (int x = 0; x < VIEW_WIDTH;x++)
	{
		for (int y = 0; y < VIEW_HEIGHT;y++)
		{
			std::list<Actor*>::iterator ite = actorobjhld[x][y].begin();
			while (ite != actorobjhld[x][y].end())
			{
				if (!(*ite)->getalive())
				{
					delete *ite;
					ite = actorobjhld[x][y].erase(ite);
				}			
				else		
					ite++;
			}
		}
	}
	//update the text 
	setDisplayText();

	//check if elaptick has reached 2000 
	if (elaptick == 2000)
	{
		if (0) //false 
		{
			string winnername;
			//get name from COMPILER 
			setWinner(winnername);
			return   GWSTATUS_PLAYER_WON; //GWSTATUS_ANT_WON; is not found in GameConsts 
		}
		else
			return GWSTATUS_NO_WINNER;
	}
	
	return GWSTATUS_CONTINUE_GAME;
	
}

void StudentWorld::cleanUp()
{
	
	for (int x = 0; x < VIEW_WIDTH;x++)
	{
		for (int y = 0; y < VIEW_HEIGHT;y++)
		{
			//freeing all Actor
			for (std::list<Actor*>::iterator ite = actorobjhld[x][y].begin(); ite != actorobjhld[x][y].end();ite++)
			{
				delete *ite;
				//ite = actorobjhld[x][y].erase(ite);
			}
		}
	}
}

bool StudentWorld::checkpebble(int x, int y) //can be replaced 
{
	for (std::list<Actor*>::iterator it = actorobjhld[x][y].begin(); it != actorobjhld[x][y].end(); ++it)
	{
		if ((*it)->isblocked())
			return true;
		else
			return false; 
	}
	return false; 
}

bool StudentWorld::findwhatsthere(int x, int y, int ID) 
{
	for (std::list<Actor*>::iterator it = actorobjhld[x][y].begin(); it != actorobjhld[x][y].end();)
	{
		if ((*it)->whatamI() == ID)
			return true;
		else
			++it;
	}
	return false; 
}

void StudentWorld::updateTickCount()
{
	elaptick++;
}

void StudentWorld::setDisplayText()
{
	
		int ticks = getCurrentTicks();
		int antsAnt0 = 0, antsAnt1 = 0, antsAnt2 = 0, antsAnt3 = 0;
		int winningAntNumber = 0;
		//antsAnt0 = getNumberOfAntsForAnt(0);
		//antsAnt1 = getNumberOfAntsForAnt(1);
		//antsAnt2 = getNumberOfAntsForAnt(2);
		//antsAnt3 = getNumberOfAntsForAnt(3);
		//winningAntNumber = getWinningAntNumber();
		// Create a string from your statistics, of the form:
		// Ticks: 1134 - AmyAnt: 32 BillyAnt: 33 SuzieAnt*: 77 IgorAnt: 05
		string s = displayFouritem(ticks,
			antsAnt0,
			antsAnt1,
			antsAnt2,
			antsAnt3,
			winningAntNumber
		);
		// Finally, update the display text at the top of the screen with your
		// newly created stats
		setGameStatText(s); // calls our provided GameWorld::setGameStatText

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

void StudentWorld::addFood(int x, int y, int health)
{
	Actor *Ptr = new food(IID_FOOD, x, y, health, this);
	actorobjhld[x][y].push_front(Ptr);
}

void StudentWorld::addActor(int x, int y, Actor * actor)
{
	actorobjhld[x][y].push_front(actor);
}

int StudentWorld::getCurrentTicks() const
{
	return elaptick;
}

Actor * StudentWorld::actor(int x, int y, int ID) 
{
	for (std::list<Actor*>::iterator it = actorobjhld[x][y].begin(); it != actorobjhld[x][y].end();)
		if ((*it)->whatamI() == ID)
			return *it;
	return nullptr;
}

string StudentWorld::displayFouritem(int ticks, int a0, int a1, int a2, int a3, int wa)
{
	string output;
	ostringstream temp;
	temp << "Ticks:";
	temp << setw(5) << ticks;
	output = temp.str();
	return output;
}


