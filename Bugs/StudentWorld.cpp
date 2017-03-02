#include "StudentWorld.h"
#include "Actor.h"
#include "Field.h"
#include "Compiler.h"
#include <string>
#include <iostream> 
#include <sstream>
#include <iomanip>
#include <algorithm>
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
	
	fileNames = getFilenamesOfAntPrograms();
	for (unsigned i = 0; i < fileNames.size(); i++)
	{
		std::string error;
		compilerForEntrant[i] = new Compiler;
		if (!compilerForEntrant[i]->compile(fileNames[i], error))
		{
			setError(fileNames[i] + " " + error);
			return GWSTATUS_LEVEL_ERROR;
		}
		n_player++;
	}


	//loading field 
	Field f;
	string fieldFile = getFieldFilename();
	//string fieldFile = "field.txt";
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
			else if (item == Field::poison)
			{
				Actor* ptr = new poison(x, y, this);
				actorobjhld[x][y].push_front(ptr);
			}
			else if (item == Field::water)
			{
				Actor* ptr = new poolofWater(x, y, this);
				actorobjhld[x][y].push_front(ptr);
			}
			else if (item == Field::anthill0)
			{
				if (n_player > 0)
				{
					Actor* ptr = new Anthill(x, y, 0, compilerForEntrant[0], this);
					actorobjhld[x][y].push_front(ptr);
				}
			}
			else if (item == Field::anthill1)
			{
				if (n_player > 1)
				{
					Actor* ptr = new Anthill(x, y, 1, compilerForEntrant[1], this);
					actorobjhld[x][y].push_front(ptr);
				}
			}
			else if (item == Field::anthill2)
			{
				if (n_player > 2)
				{
					Actor* ptr = new Anthill(x, y, 2, compilerForEntrant[2], this);
					actorobjhld[x][y].push_front(ptr);
				}
			}
			else if (item == Field::anthill3)
			{
				if (n_player > 3)
				{
					Actor* ptr = new Anthill(x, y, 3, compilerForEntrant[3], this);
					actorobjhld[x][y].push_front(ptr);
				}
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
						(*ite)->removeselfID(); //remove selfID so it can be bitten 
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
		if (getWinningAntNumber() != -1) 
		{
			string winnername = fileNames[getWinningAntNumber()];
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
	/*for (std::list<Actor*>::iterator it = actorobjhld[x][y].begin(); it != actorobjhld[x][y].end(); ++it)
	{
		if ((*it)->isblocked())
			return true;
		else
			return false; 
	}
	return false; */
	if (findwhatsthere(x, y, IID_ROCK))
		return true;
	else
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
		antsAnt0 = getNumberOfAntsForAnt(0);
		antsAnt1 = getNumberOfAntsForAnt(1);
		antsAnt2 = getNumberOfAntsForAnt(2);
		antsAnt3 = getNumberOfAntsForAnt(3);
		winningAntNumber = getWinningAntNumber();
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
		setGameStatText(s); // calls our provide GameWorld::setGameStatText

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

void StudentWorld::incre_n_ant_x(int col)
{
	switch (col)
	{
	case(0):
		n_ant_0++;
		break;
	case(1):
		n_ant_1++;
		break;
	case(2):
		n_ant_2++;
		break;
	case(3):
		n_ant_3++;
		break;
	default:
		break;
	}
}

void StudentWorld::decre_n_ant_x(int col)
{
	switch (col)
	{
	case(0):
		n_ant_0--;
		break;
	case(1):
		n_ant_1--;
		break;
	case(2):
		n_ant_2--;
		break;
	case(3):
		n_ant_3--;
		break;
	default:
		break;
	}
}

void StudentWorld::emitPhero(int x, int y, int type)
{
	int phero_type = -1;
	switch (type)
	{
	case 0:
		phero_type = IID_PHEROMONE_TYPE0;
	case 1:
		phero_type = IID_PHEROMONE_TYPE1;
	case 2:
		phero_type = IID_PHEROMONE_TYPE2;
	case 3:
		phero_type = IID_PHEROMONE_TYPE3;
	default:
		break;
	}
	if (findwhatsthere(x, y, phero_type))
	{
		if (actor(x, y, phero_type)->currHealth() == 700)
			actor(x, y, phero_type)->setHelath(768);
		else if (actor(x, y, phero_type)->currHealth() >= 512) //why the spec says this way???
			actor(x, y, phero_type)->setHelath(768);
		else
			actor(x, y, phero_type)->setHelath(actor(x, y, phero_type)->currHealth()+256);
	}
	else
	{
		Actor* ptr = new pheromone(phero_type, x, y, this);
		actorobjhld[x][y].push_front(ptr);
	}

}

int StudentWorld::getCurrentTicks() const
{
	return elaptick;
}

int StudentWorld::getNumberOfAntsForAnt(int input) const
{
	switch (input)
	{
	case(0):
		return n_ant_0;
		break;
	case(1):
		return n_ant_1;
		break;
	case(2):
		return n_ant_2;
		break;
	case(3):
		return n_ant_3;
		break;
	default:
		return -1;
		break;
	}
}

int StudentWorld::getWinningAntNumber() const
{
	int win = -1;
	int maxhld = 5;
	for (int i = 0;i < n_player;i++)
	{
		if (getNumberOfAntsForAnt(i) > maxhld)
		{
			win = i;
			maxhld = getNumberOfAntsForAnt(i);
		}
	}
	return win;
}

bool StudentWorld::isthisdangerou(int x, int y, int IDN)
{
	if (enemyonthislocation(x, y, IDN))
		return true;
	if (findwhatsthere(x, y, IID_POISON) || findwhatsthere(x, y, IID_WATER_POOL))
		return true;
	else
		return false; 
}

bool StudentWorld::isthismyanthill(int x, int y, int IDN)
{
	/*vector<int> id;
	switch (IDN)
	{
	case IID_ANT_TYPE0:
		id.push_back(IID_ANT_TYPE1);
		id.push_back(IID_ANT_TYPE2);
		id.push_back(IID_ANT_TYPE3);
		break;
	case IID_ANT_TYPE1:
		id.push_back(IID_ANT_TYPE0);
		id.push_back(IID_ANT_TYPE2);
		id.push_back(IID_ANT_TYPE3);
		break;
	case IID_ANT_TYPE2:
		id.push_back(IID_ANT_TYPE0);
		id.push_back(IID_ANT_TYPE1);
		id.push_back(IID_ANT_TYPE3);
		break;
	case IID_ANT_TYPE3:
		id.push_back(IID_ANT_TYPE0);
		id.push_back(IID_ANT_TYPE1);
		id.push_back(IID_ANT_TYPE2);
		break;
	default:
		break;
	}*/
	if (findwhatsthere(x, y, IID_ANT_HILL))
		if (actor(x, y, IID_ANT_HILL)->getColN() == IDN)
			return true;
	return false; 
}

bool StudentWorld::enemyonthislocation(int x, int y, int IDN) 
{
	vector<int> id;
	id.push_back(IID_ADULT_GRASSHOPPER);
	id.push_back(IID_BABY_GRASSHOPPER); //do you need this?
	switch (IDN)
	{
	case 0:
		id.push_back(IID_ANT_TYPE1);
		id.push_back(IID_ANT_TYPE2);
		id.push_back(IID_ANT_TYPE3);
		break;
	case 1:
		id.push_back(IID_ANT_TYPE0);
		id.push_back(IID_ANT_TYPE2);
		id.push_back(IID_ANT_TYPE3);
		break;
	case 2:
		id.push_back(IID_ANT_TYPE0);
		id.push_back(IID_ANT_TYPE1);
		id.push_back(IID_ANT_TYPE3);
		break;
	case 3:
		id.push_back(IID_ANT_TYPE0);
		id.push_back(IID_ANT_TYPE1);
		id.push_back(IID_ANT_TYPE2);
		break;
	default:
		break;
	}
	for (unsigned i = 0;i < id.size();i++)
	{
		if (findwhatsthere(x, y, id[i]))
			return true;
	}
	return false; 
}

bool StudentWorld::foodonthislocation(int x, int y)
{
	if (findwhatsthere(x, y, IID_FOOD))
		return true;
	else
		return false; 
}

bool StudentWorld::isthereathingcanbebitten(int x, int y)
{
	for (std::list<Actor*>::iterator it = actorobjhld[x][y].begin(); it != actorobjhld[x][y].end();it++)
		if (((*it)->whatamI() == IID_BABY_GRASSHOPPER || (*it)->whatamI() == IID_ADULT_GRASSHOPPER || (*it)->whatamI() == IID_ANT_TYPE0 || (*it)->whatamI() == IID_ANT_TYPE1 || (*it)->whatamI() == IID_ANT_TYPE2 || (*it)->whatamI() == IID_ANT_TYPE3) && !(*it)->getselfID())
			return true;
	return false;
}

bool StudentWorld::isthelocationjumpable(int x, int y)
{
	if (x >= VIEW_WIDTH || x < 0 || y >= VIEW_HEIGHT || y < 0)
		return false; 
	for (std::list<Actor*>::iterator it = actorobjhld[x][y].begin(); it != actorobjhld[x][y].end();it++)
	{
		if ((*it)->isblocked())
			return false; 
	}
	return true;
}

Actor * StudentWorld::actor(int x, int y, int ID) 
{
	for (std::list<Actor*>::iterator it = actorobjhld[x][y].begin(); it != actorobjhld[x][y].end();)
		if ((*it)->whatamI() == ID)
			return *it;
		else
			it++;
	return nullptr;
}

Actor * StudentWorld::aRandthingcanbebitten(int x, int y)
{
	vector<Actor*> temp_hld;
	for (std::list<Actor*>::iterator it = actorobjhld[x][y].begin(); it != actorobjhld[x][y].end(); it++)
		if (((*it)->whatamI() == IID_BABY_GRASSHOPPER || (*it)->whatamI() == IID_ADULT_GRASSHOPPER || (*it)->whatamI() == IID_ANT_TYPE0 || (*it)->whatamI() == IID_ANT_TYPE1 || (*it)->whatamI() == IID_ANT_TYPE2 || (*it)->whatamI() == IID_ANT_TYPE3) && !(*it)->getselfID())
			temp_hld.push_back(*it);
	int size = temp_hld.size();
	int pos = randInt(0,size-1);
	return temp_hld[pos];
}

std::vector<Actor*> StudentWorld::allcanbetrap(int x, int y)
{
	vector<Actor*> temp_hld;
	for (std::list<Actor*>::iterator it = actorobjhld[x][y].begin(); it != actorobjhld[x][y].end(); it++)
		if (((*it)->whatamI() == IID_BABY_GRASSHOPPER))
			temp_hld.push_back(*it);
	return temp_hld;
}

string StudentWorld::displayFouritem(int ticks, int a0, int a1, int a2, int a3, int wa)
{
	string output;
	ostringstream temp;
	temp << "Ticks:";
	temp << setw(5) << 2000-ticks;
	temp << " - ";
	output = temp.str();
	for (int i = 0; i < n_player;i++)
	{
		output += (compilerForEntrant[i]->getColonyName());
		if (i == getWinningAntNumber())
			output += '*';

		output += (": ");
		ostringstream count;
		count.fill('0');
		switch (i)
		{
		case(0):
			count << setw(2) << n_ant_0;
			break;
		case(1):
			count << setw(2) << n_ant_1;
			break;
		case(2):
			count << setw(2) << n_ant_2;
			break;
		case(3):
			count << setw(2) << n_ant_3;
			break;
		default:
			break;
		}
		output += (count.str() + " " + "ants  ");
	}

	
	return output;
}


