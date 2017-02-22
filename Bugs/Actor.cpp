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
	//lossing 1 hitpoint 
	setHelath(currHealth() - 1);

	Cord oldCo;
	oldCo.X = getX();
	oldCo.Y = getY();
	Cord newCo = oldCo;
	
	if (currHealth() <= 0)
	{
		//produce 100 food (using an insects function) 
		if (getStdW()->findwhatsthere(oldCo.X, oldCo.Y, IID_FOOD))
			getStdW()->actor(oldCo.X, oldCo.Y, IID_FOOD)->setHelath(currHealth() + 100);
		else
			getStdW()->addFood(oldCo.X, oldCo.Y, 100);
		setalive(false);
		return;
	}
	else if (Stun != 0)
	{
		setStun(getStun() - 1);
		return;
	}
	else if (currHealth() >= 1600)
	{
		//turn into adult grasshopper 
		//produce 100 food (using an insects function)
		/*std::cout << "Adult grasshopper";
		setalive(false);
		return;*/
	}
	//eat food 
	//if it eats food, it will have 50% go to sleep 
	if (getStdW()->findwhatsthere(oldCo.X, oldCo.Y, IID_FOOD))
	{
		int lefthealth = getStdW()->actor(oldCo.X, oldCo.Y, IID_FOOD)->currHealth();
		std::cout << "food curreHealth " << lefthealth << std::endl;
		if (lefthealth >= 200)
			lefthealth = 200;
		setHelath(currHealth() + lefthealth);
		std::cout << "grass hopper curreHealth " << currHealth() << std::endl;
		getStdW()->actor(oldCo.X, oldCo.Y, IID_FOOD)->setHelath(getStdW()->actor(oldCo.X, oldCo.Y, IID_FOOD)->currHealth() - lefthealth);
		if (getStdW()->actor(oldCo.X, oldCo.Y, IID_FOOD)->currHealth() == 0)
			getStdW()->actor(oldCo.X, oldCo.Y, IID_FOOD)->setalive(false);
		int a = rand() % 2;
		std::cout << "random # is " << a << std::endl;
		if (a == 0)
		{
			setStun(2);
			return;
		}
	}

	{
		if (getdisDistance() == 0)
		{
			setdisDistance(randDis(2, 10));
			disDir = randDir();
		}
		switch (disDir)
		{
		case(GraphObject::up):
			
			newCo.Y++;
			if (!getStdW()->checkpebble(newCo.X, newCo.Y))
			{
				setDirection(disDir);
				moveTo(newCo.X, newCo.Y);
				setdisDistance(getdisDistance() - 1);
				setmoved(true);
			}
			else
				setdisDistance(0);

			setStun(2);
			break;
		case(GraphObject::down):
			
			newCo.Y--;
			if (!getStdW()->checkpebble(newCo.X, newCo.Y))
			{
				setDirection(disDir);
				moveTo(newCo.X, newCo.Y);
				setdisDistance(getdisDistance() - 1);
				setmoved(true);
			}
			else
				setdisDistance(0);

			setStun(2);
			break;
		case(GraphObject::left):
			
			newCo.X--;
			if (!getStdW()->checkpebble(newCo.X, newCo.Y))
			{
				setDirection(disDir);
				moveTo(newCo.X, newCo.Y);
				setdisDistance(getdisDistance() - 1);
				setmoved(true);
			}
			else
				setdisDistance(0);

			setStun(2);
			break;
		case(GraphObject::right):
			
			newCo.X++;
			if (!getStdW()->checkpebble(newCo.X, newCo.Y))
			{
				setDirection(disDir);
				moveTo(newCo.X, newCo.Y);
				setdisDistance(getdisDistance() - 1);
				setmoved(true);
			}
			else
				setdisDistance(0);

			setStun(2);
			break;
		default:
			break;
		}
	}
	
}

void babbyGrasshopper::setdisDistance(int input)
{
	disredDistance = input;
}

void babbyGrasshopper::setStun(int input)
{
	Stun = input;
}




int babbyGrasshopper::getdisDistance() const
{
	return disredDistance;
}

int babbyGrasshopper::getStun() const
{
	return Stun;
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

void Actor::setalive(bool input)
{
	alive = input;
}

bool Actor::getalive() const
{
	return alive; 
}

int Actor::whatamI() const
{
	return ID;
}


