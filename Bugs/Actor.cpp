#include "Actor.h"
#include "StudentWorld.h"
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

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

//check stun 
bool Actor::checksleeping()
{
	if (getStun() != 0)
	{
		setStun(getStun() - 1);
		return true;
	}
	return false;
}

int Actor::currHealth() const
{
	return Health;
}

int Actor::whatamI() const
{
	return ID;
}

int Actor::getStun() const
{
	return Stun;
}

Actor* Actor::bite(int x, int y, int lost)
{
	if (getStdW()->isthereathingcanbebitten(x, y))
	{
		//std::cout << "let bite" << std::endl;
		Actor* ptr = getStdW()->aRandthingcanbebitten(x, y);
		ptr->setHelath(ptr->currHealth() - lost);
		return ptr; 
	}
	return nullptr; 
}

//int Actor::randDis(int start, int end)
//{
//	int a = rand() % (end-1) + start;
//	/*std::cout << "the random distance is " << a << std::endl;*/
//	return a;
//}

//void Actor::setX(int input)
//{
//	sx = input;
//}
//
//void Actor::setY(int input)
//{
//	sy = input;
//}

void Actor::setStun(int input)
{
	Stun = input;
}

void Actor::letStun(bool input)
{
	isStun = input;
}

//void Actor::letPoison(bool input)
//{
//	isPosion = input;
//}

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
			getStdW()->actor(oldCo.X, oldCo.Y, IID_FOOD)->setHelath(getStdW()->actor(oldCo.X, oldCo.Y, IID_FOOD)->currHealth() + 100);//this place is changed from currhelath to a pointer to health 
		else
			getStdW()->addFood(oldCo.X, oldCo.Y, 100);
		setalive(false);
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

bool insects::move()
{
	letStun(false);//once it can move, let it can be stuned 
	Cord oldCo;
	oldCo.X = getX();
	oldCo.Y = getY();
	Cord newCo = oldCo;
	switch (disDir)
	{
	case(GraphObject::up):
		newCo.Y++;
		if (!getStdW()->checkpebble(newCo.X, newCo.Y))
		{
			setDirection(disDir);
			moveTo(newCo.X, newCo.Y);
			setmoved(true);
			return true;
		}
		else
			return false;
		break;
	case(GraphObject::down):

		newCo.Y--;
		if (!getStdW()->checkpebble(newCo.X, newCo.Y))
		{
			setDirection(disDir);
			moveTo(newCo.X, newCo.Y);
			setmoved(true);
			return true;
		}
		else
			return false;
		break;
	case(GraphObject::left):

		newCo.X--;
		if (!getStdW()->checkpebble(newCo.X, newCo.Y))
		{
			setDirection(disDir);
			moveTo(newCo.X, newCo.Y);
			setmoved(true);
			return true;
		}
		else
			return false;
		break;
	case(GraphObject::right):

		newCo.X++;
		if (!getStdW()->checkpebble(newCo.X, newCo.Y))
		{
			setDirection(disDir);
			moveTo(newCo.X, newCo.Y);
			setmoved(true);
			return true;
		}
		else
			return false;
		break;
	default:
		return false;
		break;
	}
}

void insects::checkandwalk()
{
	letStun(false);//once it can move, let it can be stuned 

	Cord oldCo;
	oldCo.X = getX();
	oldCo.Y = getY();
	Cord newCo = oldCo;
	if (getdisDistance() == 0)
	{
		setdisDistance(randInt(2,10));
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
			setisbitten(false);
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
			setisbitten(false);
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
			setisbitten(false);
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
			setisbitten(false);
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

void insects::bitother(int ID, int x, int y, int input)
{
	int curhp = getStdW()->actor(x, y, ID)->currHealth();
	getStdW()->actor(x, y, ID)->setHelath(curhp - input);
}

int insects::getdisDistance() const
{
	return disredDistance;
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
		//std::cout << "aha , a new adult grasshopper" << std::endl;
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
		Actor* ptr = bite(getX(), getY(), 50);
		if (ptr != nullptr)
			if (ptr->currHealth() > 0)
			{
				if (randInt(1, 2) == 2)
					if ((ptr->whatamI() == IID_ADULT_GRASSHOPPER || ptr->whatamI() == IID_ANT_TYPE0 || ptr->whatamI() == IID_ANT_TYPE1 || ptr->whatamI() == IID_ANT_TYPE2 || ptr->whatamI() == IID_ANT_TYPE3) && !ptr->getselfID()) //will it bite an ant back????
					{
						ptr->bite(getX(), getY(), 50);
						//std::cout << "fan yao yi kou !!!!!!!!!!!!!!!!!" << std::endl;
					}
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
//=                  trap class                              =
//============================================================

//============================================================
//=                  poison class                            =
//============================================================
void poison::doSomething()
{
	vector<Actor*> hldr;
	hldr = getStdW()->allcanbetrap(getX(), getY());
	int size = hldr.size();
	
	for (int walk = 0; walk < size; walk++)
	{
		//cout << hldr[walk]->currHealth()<< "bugs health before pool" << endl;
		hldr[walk]->setHelath(hldr[walk]->currHealth() - 150);
		//cout << hldr[walk]->currHealth() << "bugs health after pool" << endl;
	}	
}

//============================================================
//=                  Pool of water class                     =
//============================================================
void poolofWater::doSomething()
{
	//set insects over it to stun 
	vector<Actor*> hldr; 
	hldr = getStdW()->allcanbetrap(getX(), getY());
	int size = hldr.size();
	for (int walk = 0; walk < size; walk++)
	{
		if (!hldr[walk]->istStun())
		{
			//cout << hldr[walk]->getStun() << "bugs health before pool" << endl;
			hldr[walk]->setStun(hldr[walk]->getStun() + 2);
			hldr[walk]->letStun(true);
			//cout << hldr[walk]->getStun() << "bugs health after pool" << endl;
		}
		//cout << "let it go" << endl;
	}

}

//============================================================
//=                  Pheromone class                         =
//============================================================
void pheromone::doSomething()
{
	setHelath(currHealth() - 1);
	if(currHealth() <= 0)
		setalive(false);
}

//============================================================
//=                     Ant   class                          =
//============================================================
void Ant::doSomething()
{
	initselfID(); //initial selfID, so it cannot bite itself
	//lossing 1 hitpoint 
	setHelath(currHealth() - 1);
	if (checkhealth())
	{
		return;
	}
		
	if (checksleeping()) //check stun 
		return;
	Compiler::Command cmd;
	for (int i = 0; i < 10;i++)
	{
		GraphObject::Direction direction = getdisDir();
		if (!m_compiler->getCommand(ic, cmd))
		{
			
			setalive(false);
			return;
		}
	
		switch (cmd.opcode)
		{
		case Compiler::moveForward:
			if (move())
			{
				setisblocked(false);
				setisbitten(false);
			}
			else
				setisblocked(true);
			ic++;
			return;
			break;
		case Compiler::eatFood:
			setfoodholder(-100);
			ic++;
			return;
			break;
		case Compiler::dropFood:
			Cord oldCo;
			oldCo.X = getX();
			oldCo.Y = getY();
			Cord newCo = oldCo;
			if (getStdW()->findwhatsthere(oldCo.X, oldCo.Y, IID_FOOD))
				getStdW()->actor(oldCo.X, oldCo.Y, IID_FOOD)->setHelath(getfoodholder());
			else
				getStdW()->addFood(oldCo.X, oldCo.Y, getfoodholder());

			ic++;
			return;
			break;
		case Compiler::bite:
			bite(getX(), getY(), 15);
			ic++;
			return;
			break;
		case Compiler::pickupFood:
			if (getfoodholder() <= 1800)
			{
				int ant_ability = 1800 - getfoodholder();
				int food_cap = getStdW()->actor(getX(), getY(), IID_FOOD)->currHealth();
				if (food_cap <= ant_ability)
				{
					if (food_cap <= 400)
					{
						setfoodholder(food_cap);
						getStdW()->actor(getX(), getY(), IID_FOOD)->setHelath(0);
						getStdW()->actor(getX(), getY(), IID_FOOD)->setalive(false);
					}
					else
					{
						setfoodholder(400);
						getStdW()->actor(getX(), getY(), IID_FOOD)->setHelath(getStdW()->actor(getX(), getY(), IID_FOOD)->currHealth() - 400);
					}
				}
				else
				{
					setfoodholder(400);
					getStdW()->actor(getX(), getY(), IID_FOOD)->setHelath(getStdW()->actor(getX(), getY(), IID_FOOD)->currHealth() - 400);
				}
			}
			ic++;
			return;
			break;
		case Compiler::emitPheromone:
			getStdW()->emitPhero(getX(), getY(), getColN());
			ic++;
			return;
			break;
		case Compiler::faceRandomDirection:
			setdisDir(randDir());
			ic++;
			return;
			break;
		case Compiler::generateRandomNumber:
			
			if (stoi(cmd.operand1) == 0)
				randNumber = 0;
			else
				randNumber = randInt(0, stoi(cmd.operand1) - 1);
			ic++;
			break;
		case Compiler::goto_command:
			ic = stoi(cmd.operand1);
			break;
		case Compiler::if_command:	
			{
				Cord oldCo;
				oldCo.X = getX();
				oldCo.Y = getY();
				Cord newCo = oldCo;
				switch (stoi(cmd.operand1))
				{
				case Compiler::last_random_number_was_zero:
					if (randInt == 0)
						ic = stoi(cmd.operand2);
					else
						ic++;
					break;
				case Compiler::i_am_carrying_food:
					if (foodholder > 0)
						ic = stoi(cmd.operand2);
					else
						ic++;
					break;
				case Compiler::i_am_hungry:
					if (currHealth() <= 25)
						ic = stoi(cmd.operand2);
					else
						ic++;
					break;
				case Compiler::i_am_standing_with_an_enemy:
					if (getStdW()->enemyonthislocation(getX(), getY(), getColN()))
						ic = stoi(cmd.operand2);
					else
						ic++;
					break;
				case Compiler::i_am_standing_on_food:
					if (getStdW()->foodonthislocation(getX(), getY()))
						ic = stoi(cmd.operand2);
					else
						ic++;
					break;
				case Compiler::i_am_standing_on_my_anthill:
					if (getStdW()->isthismyanthill(getX(), getY(), getColN()))
						ic = stoi(cmd.operand2);
					else
						ic++;
					break;
				case Compiler::i_smell_pheromone_in_front_of_me:
					
					
					int phero;
					switch (getColN())
					{
					case 0:
						phero = IID_PHEROMONE_TYPE0;
						break;
					case 1:
						phero = IID_PHEROMONE_TYPE1;
						break;
					case 2:
						phero = IID_PHEROMONE_TYPE2;
						break;
					case 3:
						phero = IID_PHEROMONE_TYPE3;
						break;
					default:
						break;
					}
					switch (direction)
					{
					case GraphObject::none:
						break;
					case GraphObject::up:
						newCo.Y++;
						break;
					case GraphObject::right:
						newCo.X++;
						break;
					case GraphObject::down:
						newCo.Y--;
						break;
					case GraphObject::left:
						newCo.X--;
						break;
					default:
						break;
					}
					if (getStdW()->findwhatsthere(newCo.X, newCo.Y, phero))
						ic = stoi(cmd.operand2);
					else
						ic++;
					break;
				case Compiler::i_smell_danger_in_front_of_me:
					
					Cord newCo1 = oldCo;
					switch (direction)
					{
					case GraphObject::none:
						break;
					case GraphObject::up:
						newCo1.Y++;
						break;
					case GraphObject::right:
						newCo1.X++;
						break;
					case GraphObject::down:
						newCo1.Y--;
						break;
					case GraphObject::left:
						newCo1.X--;
						break;
					default:
						break;
					}
					break;
					if(getStdW()->isthisdangerou(getX(),getY(),getColN()))
						ic = stoi(cmd.operand2);
					else
						ic++;
					break;
				case Compiler::i_was_bit:
					if(getisbitten())
						ic = stoi(cmd.operand2);
					else
						ic++;
					break;
				case Compiler::i_was_blocked_from_moving:
					if (getisblocked())
						ic = stoi(cmd.operand2);
					else
						ic++;
					break;
				default:
					break;
				}
			}
			break;

		default:
			break;
		}
	}
	return;
}
//============================================================
//=                   Anthill class                          =
//============================================================
void Anthill::doSomething()
{
	setHelath(currHealth() - 1);
	if (currHealth() <= 0)
		setalive(false);
	if (getStdW()->findwhatsthere(getX(), getY(), IID_FOOD))
	{
		int lefthealth = getStdW()->actor(getX(), getY(), IID_FOOD)->currHealth();
		if (lefthealth >= 10000)
			lefthealth = 10000;
		setHelath(currHealth() + lefthealth);
		getStdW()->actor(getX(), getY(), IID_FOOD)->setHelath(getStdW()->actor(getX(), getY(), IID_FOOD)->currHealth() - lefthealth);
		if (getStdW()->actor(getX(), getY(), IID_FOOD)->currHealth() == 0)
			getStdW()->actor(getX(), getY(), IID_FOOD)->setalive(false);
		return;
	}
	if (currHealth() >= 2000)
	{
		int id;
		switch (getColN())
		{
		case(0):
			id = IID_ANT_TYPE0;
			break;
		case(1):
			id = IID_ANT_TYPE1;
			break;
		case(2):
			id = IID_ANT_TYPE2;
			break;
		case(3):
			id = IID_ANT_TYPE3;
			break;
		default:
			break;
		}
		Actor* ptr = new Ant(id, getColN(), getX(), getY(), getComp(), getStdW());
		getStdW()->addActor(getX(), getY(), ptr);
		setHelath(currHealth() - 1500);
		//ASK StudentWorld to increase the count of total number of ants 
		getStdW()->incre_n_ant_x(getColN());
	}
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

