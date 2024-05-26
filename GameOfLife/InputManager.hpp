#pragma once
#include <SFML/Graphics.hpp>
#include "Grid.hpp"

struct InputManager
{
	Grid& grid;

	InputManager(Grid& grid) : grid(grid)
	{
	}

	void handleEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				int mouseX = event.mouseButton.x;
				int mouseY = event.mouseButton.y;

				handleMouseClick(mouseX, mouseY);
			}
		}
		
		else if (event.type == sf::Event::KeyPressed)
		{
			handleKeyPress(event.key.code);
		}
			
	}

	void handleMouseClick(int mouseX, int mouseY)
	{
		// calc cell indices based on mouse coords
		int rowIdx = mouseX / tileSize;
		int colIdx = mouseY / tileSize;

		grid.tiles[rowIdx][colIdx].toggleState();
	}

	void handleKeyPress(sf::Keyboard::Key keyCode)
	{
		switch (keyCode)
		{
			// pause & unpause the grid update 
			case sf::Keyboard::Space:
				grid.gamePaused = !grid.gamePaused;
				break;
		}
	}
};