//#include <SFML/Audio.hpp>
//#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
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

int gameWidth = 1360;
int gameHeight = 768;

void perspectiveGL(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
    const GLdouble pi = 3.1415926535897932384626433832795;
    GLdouble fW, fH;

    //fH = tan( (fovY / 2) / 180 * pi ) * zNear;
    fH = tan(fovY / 360 * pi) * zNear;
    fW = fH * aspect;

    glFrustum(-fW, fW, -fH, fH, zNear, zFar);
}

int main()
{
    // Get the game start time
    //std::chrono::time_point<std::chrono::system_clock> gameStartTime = std::chrono::system_clock::now();

    // Create the window
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 0;
    sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight, 32), "SFML Pong", sf::Style::Close, settings);
    window.setVerticalSyncEnabled(true);
    window.setActive(true);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.f);
    glClearColor(0.3f, 0.3f, 0.3f, 0.f);
    glDepthMask(GL_TRUE);
    glMatrixMode(GL_PROJECTION);
    perspectiveGL(90.f, (double)gameWidth / (double)gameHeight, 1.f, 300.f);    //fov, aspect, zNear, zFar

    //sf::Window window(sf::VideoMode(gameWidth, gameHeight, 32), "SFML Pong",
    //                  sf::Style::Titlebar | sf::Style::Close);
    //window.setFramerateLimit(60);
    //window.setTitle("SyntheticSchmup");
    //window.clear(sf::Color(50, 200, 50));
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
    //sf::Mouse::setPosition(sf::Vector2i(gameWidth / 2, gameHeight / 2), window);
    while (window.isOpen())
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    // Clear color and depth buffers
        window.clear(sf::Color(0, 0, 0));                      // Clear the displaty
                                                               // I don't know why we need both

        glLoadIdentity();    // Load the identity matrix

        if (!stateManager->ProcessEvents())    // Process events for the actual state
            break;                             //
        if (!stateManager->Calculate())        // Process calculation for the actual state
            break;                             //
        stateManager->Draw();                  // Draw element elements of the actual state

        window.display();    // Display the buffer
    }
    return 0;
}
