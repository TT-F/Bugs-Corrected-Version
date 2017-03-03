#include "GameWorld.h"
#include "GameConstants.h"
#include "GraphObject.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
using namespace std;

GameWorld* createStudentWorld(string);

int main()
{
	GameWorld* m_gw = createStudentWorld("dummyAssets");
	m_gw->addParameter("dummyField");
	m_gw->addParameter("dummyAnt0");

	cout << "About to call init for the StudentWorld" << endl;
	if (m_gw->init() != GWSTATUS_CONTINUE_GAME)
	{
		cout << "StudentWorld::init did not return GWSTATUS_CONTINUE_GAME" << endl;
		exit(1);
	}
	char grid[64][64];
	fill_n(&grid[0][0], 64*64, ' ');
	for (int k = 0; k < 64; k++)
	{
		grid[k][0]    = '*';
		grid[0][k]    = '*';
		grid[k][64-1] = '*';
		grid[64-1][k] = '*';
	}
	grid[5][10] = 'g';
	grid[58][53] = '0';
	GraphObject* grasshopper = nullptr;
	GraphObject::Direction dir = GraphObject::none;
	for (int layer = NUM_LAYERS - 1; layer >= 0; layer--)
	{
		auto& actors = GraphObject::getGraphObjects(layer);
		for (auto p : actors)
		{
			int x = p->getX(), y = p->getY();
			if (x == 0  ||  x == 64-1  ||  y == 0  ||  y == 64-1  ||
				(x == 10  &&  y == 5)  ||  (x == 53  &&  y == 58))
			{
				if (grid[y][x] == ' ')
				{
					cout << "Unexpected second object at x=" << x << ",y=" << y << endl;
					exit(1);
				}
				grid[y][x] = ' ';
				if (y == 5  &&  x == 10)
				{
					grasshopper = p;
					dir = grasshopper->getDirection();
					cout << "get dir" << dir <<endl;
				}
			}
		}
	}
	for (int x = 0; x < 64; x++)
	{
		for (int y = 0; y < 64; y++)
		{
			if (grid[y][x] != ' '  &&  !(x == 53  &&  y == 58))
			{
				cout << "Missing object at x=" << x << ",y=" << y << endl;
				exit(1);
			}
		}
	}
	cout << "About to call move for the StudentWorld" << endl;
	if (m_gw->move() != GWSTATUS_CONTINUE_GAME)
	{
		cout << "StudentWorld::move did not return GWSTATUS_CONTINUE_GAME" << endl;
		exit(1);
	}
	
	int x = grasshopper->getX(), y = grasshopper->getY();
	
	cout << "x" << x << "y" << y << "dir" << dir <<endl;
	if (!(x == 10  &&  y == 4  &&  dir == GraphObject::down)  &&
		!(x == 10  &&  y == 6  &&  dir == GraphObject::up)  &&
		!(x == 9   &&  y == 5  &&  dir == GraphObject::left)  &&
		!(x == 11  &&  y == 5  &&  dir == GraphObject::right))
	{
		cout << "Baby grasshopper did not move one step from x=10,y=5 in the correct direction" << endl;
		exit(1);
	}
	cout << "About to call cleanUp for the StudentWorld" << endl;
	m_gw->cleanUp();
	cout << "About to delete the StudentWorld" << endl;
	delete m_gw;
	cout << "****** SUCCESS! Passed the sanity check. ******" << endl;
}
