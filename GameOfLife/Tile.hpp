#pragma once
#include "Constants.hpp"

// TODO
// should communicate with game class, does not care about what is happening in the world
// only cares about itself, i.e., the individual state of the tile
// update method for assigning alive/dead states of tiles

struct Tile
{
	int x;
	int y;
	
	bool isAlive = false;

	Tile(int x_coord, int y_coord) : x(x_coord), y(y_coord)
	{
	}

	void setDead() 
	{
		isAlive = false;
	}

	void setAlive() 
	{
		isAlive = true;
	}

	void toggleState()
	{
		this->isAlive = !this->isAlive;
	}
};