#pragma once
#include "Tile.hpp"
#include "Constants.hpp"
#include <vector>
#include <iostream>
#include <random>

// TODO
// should communicate with game and tile
// should create tile grid in constructor
// should employ conways logic in update, probably
// could have utility fncs like reset, placing your own tiles, saving loading etc

struct Grid
{
	int w;
	int h;
	bool gamePaused = true;

	std::vector<std::vector<Tile>> tiles; // 2d array of tiles, separate from rendered grid of lines

	Grid() : w(gameWidth), h(gameHeight)
	{
		generateGridOfDeadTiles();
		setRandomLiveTiles();
	}

	void update()
	{
		// iterate through all tiles
		// check each rule for each tile 
		// change states of each tile
		if (!gamePaused) {
			// copy grid to achieve simultaneous state changes 
			std::vector<std::vector<Tile>> tilesCopy = tiles;

			for (size_t i = 0; i < tiles.size() - 1; i++) {
				for (size_t j = 0; j < tiles.size() - 1; j++) {
					Tile& tile = tiles[i][j]; // use & to ensure the tile is not a copy, since we edit the tiles directly
					Tile& newTile = tilesCopy[i][j];

					std::vector<Tile> neighbors = getTileNeighbors(i, j); // get its neighbors
					int numLivingNeighbors = 0;

					// iterate through 8 surrounding neighbor tiles
					// to get the number of living tiles near the current tile
					for (Tile& neighbor : neighbors)
					{
						if (neighbor.isAlive)
						{
							numLivingNeighbors++;
						}
					}
					// Apply the rules of the Game of Life
					if (tile.isAlive) 
					{
						if (numLivingNeighbors < 2 || numLivingNeighbors > 3) 
						{
							// Any live cell with fewer than two live neighbors dies (underpopulation)
							// Any live cell with more than three live neighbors dies (overpopulation)
							newTile.setDead();
						}
					}
					else
					{
						if (numLivingNeighbors == 3)
						{
							// Any dead cell with exactly three live neighbors becomes a live cell (reproduction)
							newTile.setAlive();
						}
					}
				}
			}
			tiles = tilesCopy; // set all state changes at the same time
		}
	}

	std::vector<Tile> getTileNeighbors(size_t i, size_t j)
	{
		std::vector<Tile> neighbors;

		// iterate over neighboring indices
		for (int xOffset = -1; xOffset <= 1; xOffset++)
		{
			for (int yOffset = -1; yOffset <= 1; yOffset++)
			{
				if (xOffset == 0 && yOffset == 0) continue; // skip current tile

				// calculate neighbor indices with wrap-around
				// remove the -1's and turn on random tiles for the edge glitch which produces interesting fractal designs
				int neighborI = (static_cast<int>(i) + xOffset + totalGridTiles) % (totalGridTiles);
				int neighborJ = (static_cast<int>(j) + yOffset + totalGridTiles) % (totalGridTiles);

				// add the wrapped-around neighbor to the list
				neighbors.push_back(tiles[neighborI][neighborJ]);
			}
		}
		return neighbors;
	}

	void generateGridOfDeadTiles()
	{
		tiles.resize(totalGridTiles); // set number of rows 

		for (size_t i = 0; i < totalGridTiles; i++) {
			tiles[i].reserve(totalGridTiles); // reserve space for number of columns in each row
			for (size_t j = 0; j < totalGridTiles; j++) {
				tiles[i].emplace_back(i, j); // only need Tile arguments because tiles is a vector of tile objects
			}
		}
	}

	void setRandomLiveTiles()
	{
		for (int i = 0; i < 10; i++) {
			// get random starting indices
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dis(0, 100);

			int threshold = 60; // % chance to spawn a live tile

			for (int i = 0; i < tiles.size(); i++)
			{
				for (int j = 0; j < tiles[i].size(); j++)
				{
					int val = dis(gen);
					if (val > threshold) 
					{
						tiles[i][j].setAlive();
					}
				}
			}
		}
	}
};