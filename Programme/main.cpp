#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

#include "StateManager.h"
#include "StateMenu.h"

using namespace std;

void exitWithMessage(int p_error, std::string p_message = "No message")
{
    std::cout << p_message << std::endl;
    exit(p_error);
}

int gameWidth = 1024;
int gameHeight = 768;

int main()
{
    // Get the game start time
    //std::chrono::time_point<std::chrono::system_clock> gameStartTime = std::chrono::system_clock::now();

    // Create the window
    sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight, 32), "SFML Pong",
                            sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    window.setTitle("SyntheticSchmup");
    window.clear(sf::Color(50, 200, 50));
    window.setMouseCursorVisible(false);

    // Set the game manager with the first state of the game
    auto stateManager = std::make_shared<StateManager>();
    stateManager->PushState(std::make_shared<StateMenu>(stateManager, window));

    for (unsigned int i = 0; i < 7; i++)
    {
        if (sf::Joystick::isConnected(i))
            std::cout << "connected : " << i << std::endl;
    }

    // Set the mouse position to the center of the windows at the beginin of the game
    sf::Mouse::setPosition(sf::Vector2i(gameWidth / 2, gameHeight / 2), window);
    while (window.isOpen())
    {
        if (!stateManager->ProcessEvents())
            break;
        if (!stateManager->Calculate())
            break;
        window.clear(sf::Color(250, 180, 20));
        stateManager->Draw();

        window.display();
    }
    return 0;
}
