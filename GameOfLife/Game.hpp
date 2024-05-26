#pragma once
#include "Renderer.hpp"
#include "Tile.hpp"
#pragma once
#include "Grid.hpp"
#include "Constants.hpp"
#include "InputManager.hpp"

struct Game 
{
    sf::RenderWindow& window;
    Grid grid;
    InputManager ip;

    Game(sf::RenderWindow& win) : window(win), grid(), ip(grid)
	{
        Run();
	}

    void Run()
    {
        Renderer renderer(window, grid);

        // run the main loop
        while (window.isOpen())
        {
            // handle events
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                else
                    ip.handleEvent(event);
            }
            renderer.render(); // general render function which calls all render functions in renderer.hpp
            grid.update(); // updates all tile states with logic applied
        }
    }
};

//todo: see if removing the grid-line renderer does anything for optimization
//add option to clear board / reset board
//add clicking and dragging 
//look into threading for massive simulations
//look into color gradients based on screen location
//maybe add a menu / loading screen, and a selection for the buggy version i had without copying, could be cool larger scale
