#include "Actor.h"
#include "StudentWorld.h"
#include <iostream>
#include <cmath>


// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp
//============================================================
//=                      base class                          =
//============================================================

void Actor::setHelath(int wantedHealth)
{
	Health = wantedHealth;
}

void Actor::setmoved(bool input)
{
	moved = input;
}

void Actor::setalive(bool input)
{
	alive = input;
}

bool Actor::getalive() const
{
	return alive;
}

bool Actor::isblocked() const
{
	return blocked;
}

bool Actor::ismoved() const
{
	return moved;
}

int Actor::currHealth() const
{
	return Health;
}

int Actor::whatamI() const
{
	return ID;
}

Actor* Actor::bite(int x, int y)
{
	if (getStdW()->isthereathingcanbebitten(x, y))
	{
		//std::cout << "let bite" << std::endl;
		Actor* ptr = getStdW()->aRandthingcanbebitten(x, y);
		ptr->setHelath(ptr->currHealth() - 50);
		return ptr; 
	}
	return nullptr; 
}

int Actor::randDis(int start, int end)
{
	int a = rand() % (end-1) + start;
	/*std::cout << "the random distance is " << a << std::endl;*/
	return a;
}

void Actor::setX(int input)
{
	sx = input;
}

void Actor::setY(int input)
{
	sy = input;
}

StudentWorld * Actor::getStdW() const
{
	return m_world;
}

//============================================================
//=                      insects class                       =
//============================================================

bool insects::checkhealth()
{
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
		return true;
	}
	return false;
}

bool insects::checksleeping()
{
	if (getStun() != 0)
	{
		setStun(getStun() - 1);
		return true;
	}
	return false;
}

bool insects::eatfood()
{
	Cord oldCo;
	oldCo.X = getX();
	oldCo.Y = getY();
	Cord newCo = oldCo;
	if (getStdW()->findwhatsthere(oldCo.X, oldCo.Y, IID_FOOD))
	{
		int lefthealth = getStdW()->actor(oldCo.X, oldCo.Y, IID_FOOD)->currHealth();
		//std::cout << "food curreHealth " << lefthealth << std::endl;
		if (lefthealth >= 200)
			lefthealth = 200;
		setHelath(currHealth() + lefthealth);
		//std::cout << "grass hopper curreHealth " << currHealth() << std::endl;
		getStdW()->actor(oldCo.X, oldCo.Y, IID_FOOD)->setHelath(getStdW()->actor(oldCo.X, oldCo.Y, IID_FOOD)->currHealth() - lefthealth);
		if (getStdW()->actor(oldCo.X, oldCo.Y, IID_FOOD)->currHealth() == 0)
			getStdW()->actor(oldCo.X, oldCo.Y, IID_FOOD)->setalive(false);
		return true;
	}
	return false; 
}

bool insects::randomsleep()
{
	int a = rand() % 2;
	//std::cout << "random # is " << a << std::endl;
	if (a == 0)
	{
		setStun(2);
		return true;
	}
	return false;
}

void insects::checkandwalk()
{
	Cord oldCo;
	oldCo.X = getX();
	oldCo.Y = getY();
	Cord newCo = oldCo;
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

Cord insects::radiusten()
{
	Cord mvCo;
	
	mvCo.X = 0;
	mvCo.Y = 0;
	mvCo.X = randInt(1, 10);
	mvCo.Y = randInt(1, 10);
	if (randInt(0, 1) == 1)
		mvCo.X = mvCo.X*(-1);
	if (randInt(0, 1) == 1)
		mvCo.Y = mvCo.Y*(-1);
	if ( pow(mvCo.X, 2)+ (mvCo.Y, 2) > 100)
		mvCo = radiusten();
	return mvCo;
}

void insects::setdisDistance(int input)
{
	disredDistance = input;
}

void insects::setStun(int input)
{
	Stun = input;
}

void insects::bitother(int ID, int x, int y, int input)
{
	int curhp = getStdW()->actor(x, y, ID)->currHealth();
	getStdW()->actor(x, y, ID)->setHelath(curhp - input);
}

int insects::getdisDistance() const
{
	return disredDistance;
}

int insects::getStun() const
{
	return Stun;
}

//============================================================
//=                  babbygrasshopper class                  =
//============================================================
void babbyGrasshopper::doSomething()
{
	//lossing 1 hitpoint 
	setHelath(currHealth() - 1);
	
	if (checkhealth())
		return;
	if (checksleeping())
		return;
	if (currHealth() >= 1600)
	{
		Cord oldCo;
		oldCo.X = getX();
		oldCo.Y = getY();
		Cord newCo = oldCo;
		Actor* act = new adultGrasshopper(getX(), getY(), getStdW());
		getStdW()->addActor(getX(), getY(), act);
		if (getStdW()->findwhatsthere(oldCo.X, oldCo.Y, IID_FOOD))
			getStdW()->actor(oldCo.X, oldCo.Y, IID_FOOD)->setHelath(getStdW()->actor(oldCo.X, oldCo.Y, IID_FOOD)->currHealth() + 100);
		else
			getStdW()->addFood(oldCo.X, oldCo.Y, 100);
		setalive(false);
		return;
	}
	//eat food 
	if (eatfood())
		if (randomsleep())
			return;
	checkandwalk();	
}

//============================================================
//=                 addultgrasshopper class                  =
//============================================================
void adultGrasshopper::doSomething()
{
	//lossing 1 hitpoint 
	setHelath(currHealth() - 1);
	initselfID(); //initial selfID, so it cannot bite itself
	if (checkhealth())
		return;
	else if (checksleeping())
		return;
	//1/3 chance bite 
	if (randInt(1, 3) == 1)
	{
		//std::cout << "bite" << std::endl;
		//if there are more than one enemy on this location 
		Actor* ptr = bite(getX(), getY());
		if (ptr != nullptr)
			if (randInt(1, 2) == 2)
				if (ptr->whatamI() == IID_ADULT_GRASSHOPPER && !ptr->getselfID())
				{
					ptr->bite(getX(), getY());
					//std::cout << "fan yao yi kou !!!!!!!!!!!!!!!!!" << std::endl;
				}
					
	}
	//else 1/10 chance to jump 
	else if (randInt(1, 10) == 1)
	{	
			Cord newloc = radiusten();
			while (!getStdW()->isthelocationjumpable(getX()+newloc.X, getY()+newloc.Y))
				newloc = radiusten();
			//move to new location 
			//std::cout << "aha  it moved ========================================" << std::endl;
			moveTo(getX()+newloc.X, getY()+newloc.Y);
			setStun(2);
			return;
	}

	//eat food 
	if (eatfood())
		if (randomsleep())
			return;
	checkandwalk();
}

//============================================================
//=                  poison class                            =
//============================================================
void poison::doSomething()
{
}

//============================================================
//=                  Pool of water class                     =
//============================================================
void poolofWater::doSomething()
{
	//set insects over it to stun 

}

//============================================================
//=                 utility                                  =
//============================================================
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


