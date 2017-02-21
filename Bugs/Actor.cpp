#include "Actor.h"
#include "StudentWorld.h"
#include <iostream>

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

//base class 

void Actor::setHelath(int wantedHealth)
{
	Health = wantedHealth;
}

void Actor::setmoved(bool input)
{
	moved = input;
}

int Actor::randDis(int start, int end)
{
	int a = rand() % (end-1) + start;
	/*std::cout << "the random distance is " << a << std::endl;*/
	return a;
}

bool Actor::isblocked() const
{
	return blocked;
}


int Actor::currHealth() const
{
	return Health;
}

StudentWorld * Actor::getStdW() const
{
	return m_world;
}

bool Actor::ismoved() const
{
	return moved;
}

//int Actor::whatamI() const
//{
//	return ID;
//}


//baby grass hopper 

void babbyGrasshopper::doSomething()
{
	Cord oldCo;
	oldCo.X = getX();
	oldCo.Y = getY();
	Cord newCo = oldCo;
	if (getdisDistance() != 0)
	{
		switch (disDir)
		{
		case(GraphObject::up):
			
			newCo.Y++;
			if (!getStdW()->checkpebble(newCo.X, newCo.Y))
			{
				setDirection(disDir);
				moveTo(newCo.X, newCo.Y);
			}
			setdisDistance(getdisDistance() - 1);
			break;
		case(GraphObject::down):
			
			newCo.Y--;
			if (!getStdW()->checkpebble(newCo.X, newCo.Y))
			{
				setDirection(disDir);
				moveTo(newCo.X, newCo.Y);
			}
			setdisDistance(getdisDistance() - 1);
			break;
		case(GraphObject::left):
			
			newCo.X--;
			if (!getStdW()->checkpebble(newCo.X, newCo.Y))
			{
				setDirection(disDir);
				moveTo(newCo.X, newCo.Y);
			}
			setdisDistance(getdisDistance() - 1);
			break;
		case(GraphObject::right):
			
			newCo.X++;
			if (!getStdW()->checkpebble(newCo.X, newCo.Y))
			{
				setDirection(disDir);
				moveTo(newCo.X, newCo.Y);
			}
			setdisDistance(getdisDistance() - 1);
			break;
		default:
			break;
		}
	}
	else
	{
		setdisDistance(randDis(2, 10));
		disDir = randDir();
	}
	
	//set moved checking condition 
	setmoved(true);

	//lossing 1 hitpoint 
	//setHelath(currHealth() - 1);
}

void babbyGrasshopper::setdisDistance(int input)
{
	disredDistance = input;
}


int babbyGrasshopper::getdisDistance() const
{
	return disredDistance;
}



GraphObject::Direction randDir()
{
	int a = rand() % 4;
	/*std::cout << "the random direction generated is " << a << std::endl;*/
	switch (a)
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


