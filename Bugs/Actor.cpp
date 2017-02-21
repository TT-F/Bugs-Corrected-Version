#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

//base class 

//Actor::~Actor()
//{
//}

void Actor::setHelath(int wantedHealth)
{
	Health = wantedHealth;
}

int Actor::randDis(int start, int end)
{
	return rand() % end + start;
}


int Actor::currHealth() const
{
	return Health;
}

StudentWorld * Actor::getStdW() const
{
	return m_world;
}



int Actor::whatamI() const
{
	return ID;
}


//pebble class 

void pebble::doSomething()
{
}


//baby grass hopper 

void babbyGrasshopper::doSomething()
{
	//The BabyGrasshopper must pick a random distance to walk in this random direction. The distance must be between[2, 10], inclusive.
	switch (randDir())
	{
	case(GraphObject::up):
		if (checkSurr(getX(), getY() + randDis(2, 10)))
		{
			setDirection(GraphObject::up);
			moveTo(getX(), getY() + randDis(2, 10));
			break;
		}
	case(GraphObject::down):
		if (checkSurr(getX(), getY() - randDis(2, 10)))
		{
			setDirection(GraphObject::down);
			moveTo(getX(), getY() - randDis(2, 10));
			break;
		}
	case(GraphObject::left):
		if (checkSurr(getX() - randDis(2, 10), getY()))
		{
			setDirection(GraphObject::left);
			moveTo(getX() - randDis(2, 10), getY());
			break;
		}
	case(GraphObject::right):
		if (checkSurr(getX() + randDis(2, 10), getY()))
		{
			setDirection(GraphObject::right);
			moveTo(getX() + randDis(2, 10), getY());
			break;
		}
	default:
		break;
	}

	//lossing 1 hitpoint 
	//setHelath(currHealth() - 1);
}

bool babbyGrasshopper::checkSurr(int x, int y)
{
	//find the object in the StudentWorld's list that matches the same location 
	if (getStdW()->find(x, y) != nullptr)
	{
		//check if that location has a rock 
		if (getStdW()->find(x, y)->whatamI() == IID_ROCK) //can I use getID() from GameWorld??
			return false;
		else
			//return true if it does't have one 
			return true;
	}
	return false;
}

GraphObject::Direction randDir()
{
	switch (rand() % 4)
	{
	case 0:
		return GraphObject::up;
		break;
	case 1:
		return GraphObject::right;
		break;
	case 2:
		return GraphObject::down;
		break;
	case 3:
		return GraphObject::left;
		break;
	default:
		return GraphObject::none;
		break;
	}
}
