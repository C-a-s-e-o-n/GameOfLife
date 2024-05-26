#include "Game.hpp"
#include "Constants.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight), "GameOfLife");
    
    Game game(window);
}