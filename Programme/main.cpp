
#include "SyntheticSchmup.h"

#include <chrono>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <iostream>
#include <string>

#include "StateManager.h"
#include "StateMenu.h"

using namespace std;

SyntheticSchmup * instance = SyntheticSchmup::Get();

void perspectiveGL(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
    GLdouble fW, fH;
    aspect;
    //fH = tan( (fovY / 2) / 180 * pi ) * zNear;
    fW = tan(fovY / 360 * M_PI) * zNear;
    fH = fW * aspect;
    std::cout << fH << ":" << fW << std::endl;

    glFrustum(-fW, fW, -fH, fH, zNear, zFar);
}

int main()
{
    int width = 1360, height = 768;
    double fov = 90;
    instance->Initialize(width, height, fov);
    // Get the game start time
    //std::chrono::time_point<std::chrono::system_clock> gameStartTime = std::chrono::system_clock::now();

    // Create the window
    instance->settings.depthBits = 24;
    instance->settings.stencilBits = 8;
    instance->settings.antialiasingLevel = 4;
    instance->settings.majorVersion = 3;
    instance->settings.minorVersion = 0;
    sf::RenderWindow window(sf::VideoMode(instance->windowWidth, instance->windowHeight, 32), "SyntheticSchmup", sf::Style::Default, instance->settings);
    //sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight, 32), "SFML Pong", sf::Style::Close, settings);
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    window.setActive(true);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearDepth(1.f);
    glClearColor(0.3f, 0.3f, 0.3f, 0.f);
    glDepthMask(GL_TRUE);
    glMatrixMode(GL_PROJECTION);
    perspectiveGL(instance->windowFov, instance->windowRatio, 0.8, 300.);    //fov, aspect, zNear, zFar

    window.setMouseCursorVisible(false);

    // Set the game manager with the first state of the game
    auto stateManager = std::make_shared<StateManager>();
    stateManager->PushState(std::make_shared<StateMenu>(stateManager, window));

    for (unsigned int i = 0; i < 7; i++)
    {
        if (sf::Joystick::isConnected(i))
            std::cout << "Controller connected : " << i << std::endl;
    }

    // Set the mouse position to the center of the windows at the beginin of the game
    //sf::Mouse::setPosition(sf::Vector2i(gameWidth / 2, gameHeight / 2), window);
    instance->soundMap.at("music").SetVolume(10);
    instance->soundMap.at("music").Play();
    while (window.isOpen())
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    // Clear color and depth buffers
        window.clear(sf::Color(0, 0, 0));                      // Clear the display
                                                               // I don't know why we need both

        glLoadIdentity();    // Load the identity matrix

        if (!stateManager->ProcessEvents())    // Process events for the actual state
            break;                             //
        if (!stateManager->Calculate())        // Process calculation for the actual state
            break;                             //
        stateManager->Draw();                  // Draw element elements of the actual state

        // Draw the XYZ arrows
        glPushMatrix();
        {
            glTranslated(0, 0, -2.1);
            glBegin(GL_LINES);
            {
                glColor3d(1, 0, 0);
                glVertex3d(0, 0, 0);
                glVertex3d(1, 0, 0);

                glColor3d(0, 1, 0);
                glVertex3d(0, 0, 0);
                glVertex3d(0, 1, 0);

                glColor3d(0, 0, 1);
                glVertex3d(0, 0, 0);
                glVertex3d(0, 0, 1);
            }
            glEnd();
        }
        glPopMatrix();

        // Little lambda function to draw plain circles
        std::function<void(double, double, double, double, int)> DrawCircle = [](double cx, double cy, double cz, double r, int num_segments) {
            glPushMatrix();
            {
                glTranslated(cx, cy, cz);
                glColor3d(1, 0.5, 0.5);
                glBegin(GL_POLYGON);
                for (int ii = 0; ii < num_segments; ii++)
                {
                    double theta = 2.0f * M_PI * double(ii) / double(num_segments);
                    double x = r * cos(theta);
                    double y = r * sin(theta);
                    glVertex2d(x, y);
                }
                glEnd();
                glColor3d(1, 1, 1);
            }
            glPopMatrix();
        };

        // Draw circles in each corners, and in the middle of left, right, top and bottom border of the window
        double depth = -1.;
        Vector2d limits = instance->GetXYLimits(depth);
        double right = limits.x;
        double top = limits.y;
        double left = -right;
        double bottom = -top;
        double radius = 0.01 * depth;
        DrawCircle(left, 0, depth, radius, 20);
        DrawCircle(left, top, depth, radius, 20);
        DrawCircle(0, top, depth, radius, 20);
        DrawCircle(right, top, depth, radius, 20);
        DrawCircle(right, 0, depth, radius, 20);
        DrawCircle(right, bottom, depth, radius, 20);
        DrawCircle(0, bottom, depth, radius, 20);
        DrawCircle(left, bottom, depth, radius, 20);

        window.display();    // Display the buffer

        stateManager->ExecutePop();
    }
    return 0;
}
