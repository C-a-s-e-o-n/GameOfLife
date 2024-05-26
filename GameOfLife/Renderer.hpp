#pragma once
#include <SFML/Graphics.hpp> // be careful, double inclusion leads to bugs without error messages :D
#include "Constants.hpp"
#include "Grid.hpp"
#include <iostream>

struct Renderer
{
    sf::RenderWindow& window;
    Grid& grid;

    // Render Window is non-copyable so pass it by reference
    // and use an initialization list before the constructor executes
    Renderer(sf::RenderWindow& win, Grid& grid) : window(win), grid(grid)
    {
    }

    void render()
    {
        renderGrid();
        renderTiles();
        window.display();
    }

    void renderGrid()
    {
        window.clear(sf::Color::Black);

        const int numLinesX = window.getSize().x / tileSize + 1;
        const int numLinesY = window.getSize().y / tileSize + 1;
        const int totalVertices = 2 * (numLinesX + numLinesY);

        sf::VertexArray lines(sf::Lines, totalVertices);
        int index = 0;

        // horizontal lines
        for (size_t i = 0; i <= window.getSize().y; i += tileSize)
        {
            lines[index++] = sf::Vertex(sf::Vector2f(0, i), sf::Color(255, 255, 255, 255));
            lines[index++] = sf::Vertex(sf::Vector2f(window.getSize().x, i), sf::Color(255, 255, 255, 255));
        }

        for (size_t i = 0; i <= window.getSize().x; i += tileSize)
        {
            lines[index++] = sf::Vertex(sf::Vector2f(i, 0), sf::Color(255, 255, 255, 255));
            lines[index++] = sf::Vertex(sf::Vector2f(i, window.getSize().y), sf::Color(255, 255, 255, 255));
        }
        window.draw(lines);
    }

    void renderTiles() 
    {
        // create vector of square objects for batch drawing optimization
        sf::VertexArray squares(sf::Triangles);

        // create a square to be drawn on line-based grid
        sf::RectangleShape square(sf::Vector2f(tileSize, tileSize));

        for (size_t i = 0; i < grid.tiles.size(); i++)
        {
            for (size_t j = 0; j < grid.tiles[i].size(); j++)
            {
                // extract tile from vector-based grid
                Tile& tile = grid.tiles[i][j];

                float x = tile.x * tileSize;
                float y = tile.y * tileSize;

                // define vertices of the square
                squares.append(sf::Vertex(sf::Vector2f(x, y), sf::Color::Black));
                squares.append(sf::Vertex(sf::Vector2f(x + tileSize, y), sf::Color::Black));
                squares.append(sf::Vertex(sf::Vector2f(x, y + tileSize), sf::Color::Black));

                squares.append(sf::Vertex(sf::Vector2f(x + tileSize, y), sf::Color::Black));
                squares.append(sf::Vertex(sf::Vector2f(x + tileSize, y + tileSize), sf::Color::Black));
                squares.append(sf::Vertex(sf::Vector2f(x, y + tileSize), sf::Color::Black));

                // Set square color based on tile state
                if (tile.isAlive)
                {
                    // Change color if the tile is alive
                    for (int k = 0; k < 6; ++k)
                        squares[squares.getVertexCount() - k - 1].color = sf::Color(255, 255, 255, 240);
                }
                else
                {
                    // Change color if the tile is dead
                    for (int k = 0; k < 6; ++k)
                        squares[squares.getVertexCount() - k - 1].color = sf::Color(0, 0, 0, 210);
                }

            }
        }
        // draw square on line-based grid based on position in vector-based grid
        window.draw(squares);
    }
};