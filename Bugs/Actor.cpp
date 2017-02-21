#include "Actor.h"
#include "StudentWorld.h"
#include <iostream>

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
	int a = rand() % (end-1) + start;
	std::cout << "the random distance is " << a << std::endl;
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

//int Actor::whatamI() const
//{
//	return ID;
//}


//pebble class 

//void pebble::doSomething()
//{
//}


//baby grass hopper 

void babbyGrasshopper::doSomething()
{
	Cord Co;
	//The BabyGrasshopper must pick a random distance to walk in this random direction. The distance must be between[2, 10], inclusive.
	switch (randDir())
	{
	case(GraphObject::up):
		std::cout << "up ";
		Co.X = getX();
		Co.Y = getY() + randDis(2, 10);
		if (checkSurr(Co.X,Co.Y,getX(),getY()))
		{
			std::cout << "SUCCESS UP " <<std::endl;
			setDirection(GraphObject::up);
			moveTo(Co.X, Co.Y);
			break;
		}
	case(GraphObject::down):
		std::cout << "down ";
		Co.X = getX();
		Co.Y = getY() - randDis(2, 10);
		if (checkSurr(Co.X, Co.Y, getX(), getY()))
		{
			std::cout << "SUCCESS down " << std::endl;
			setDirection(GraphObject::down);
			moveTo(Co.X, Co.Y);
			break;
		}
	case(GraphObject::left):
		std::cout << "left ";
		Co.X = getX() - randDis(2, 10);
		Co.Y = getY();
		if (checkSurr(Co.X, Co.Y, getX(), getY()))
		{
			std::cout << "SUCCESS left " << std::endl;
			setDirection(GraphObject::left);
			moveTo(Co.X, Co.Y);
			break;
		}
	case(GraphObject::right):
		std::cout << "right ";
		Co.X = getX() + randDis(2, 10);
		Co.Y = getY();
		if (checkSurr(Co.X, Co.Y, getX(), getY()))
		{
			std::cout << "SUCCESS right " << std::endl;
			setDirection(GraphObject::right);
			moveTo(Co.X, Co.Y);
			break;
		}
	default:
		break;
	}

	//lossing 1 hitpoint 
	//setHelath(currHealth() - 1);
}

bool babbyGrasshopper::checkSurr(int x, int y, int ox, int oy)
{
	if (!inbound(x, y))
		return false;
	if (y == oy)
	{
		for (int xx = ox; xx <= x;xx++)
		{
			if (getStdW()->find(xx, y) != nullptr)
				if ((getStdW()->find(xx, y)->isblocked())) //can I use getID() from GameWorld??
				{
					std::cout << "NOT ALLOWED IN XX" << std::endl;
					return false;
				}
					
		}
	}
	if (x == ox)
	{
		for (int yy = oy; yy <= y;yy++)
		{
			if (getStdW()->find(x, yy) != nullptr)
				if ((getStdW()->find(x, yy)->isblocked())) //can I use getID() from GameWorld??
				{
					std::cout << "NOT ALLOWED IN YY" << std::endl;
					return false;
				}
		}
	}

	return true;
}

GraphObject::Direction randDir()
{
	int a = rand() % 4;
	std::cout << "the random direction generated is " << a << std::endl;
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

bool inbound(int x, int y)
{
	if (x<1 || x>VIEW_WIDTH - 1)
		return false;
	if (y<1 || y>VIEW_HEIGHT - 1)
		return false;
}
