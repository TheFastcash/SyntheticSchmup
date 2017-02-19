
#include <iostream>

#include "StateGame.h"

StateGame::StateGame(std::shared_ptr<StateManager> p_stateManager,
                     sf::RenderWindow & p_window)
  : IState(p_stateManager, p_window)
  , m_ship()
{
}

bool StateGame::Calculate()
{
    sf::Time timeSpent = m_clock.getElapsedTime();
    m_clock.restart();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        m_ship.Position() += sf::Vector2f(m_ship.Speed() * timeSpent.asSeconds(), 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        m_ship.Position() += sf::Vector2f(-m_ship.Speed() * timeSpent.asSeconds(), 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        m_ship.Position() += sf::Vector2f(0, -m_ship.Speed() * timeSpent.asSeconds());
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        m_ship.Position() += sf::Vector2f(0, m_ship.Speed() * timeSpent.asSeconds());
    }

    std::cout << m_ship.Position().x << ":" << m_ship.Position().y << std::endl;
    return true;
}

bool StateGame::Draw()
{
    // Draw the background
    glPushMatrix();
    {
        //sf::Texture::bind(&m_backgroundTexture);
        glTranslatef(0.f, 0.f, -20.f);    // Don't put 0.f for 'z' axis, or the square won't be shown
        //glRotatef(25.f, 1.f, 0.f, 0.f);
        glBegin(GL_QUADS);    //draw some squares
        {
            glColor3d(0, 0.2, 0.7);
            glVertex3f(-1, 1, 0);
            glColor3d(0.2, 0.7, 0);
            glVertex3f(-1, -1, 0);
            glColor3d(0.7, 0, 0.2);
            glVertex3f(1, -1, 0);
            glColor3d(1, 1, 1);
            glVertex3f(1, 1, 0);
        }
        glEnd();
    }
    glPopMatrix();
    glPushMatrix();
    {
        float sizeX = m_ship.Size().x / 2;
        float sizeY = m_ship.Size().y / 2;
        float posX = m_ship.Position().x;
        float posY = m_ship.Position().y;
        sf::Texture::bind(&m_ship.Texture());
        glTranslatef(-posX, -posY, -10.f);    // Don't put 0.f for 'z' axis, or the square won't be shown
        glBegin(GL_QUADS);                    //draw some squares
        {
            //float ratio = x / y;
            glTexCoord2f(0, 0);
            glVertex3f(-sizeX / 2, sizeY / 2, 0);
            glTexCoord2f(0, 1);
            glVertex3f(-sizeX / 2, -sizeY / 2, 0);
            glTexCoord2f(1, 1);
            glVertex3f(sizeX / 2, -sizeY / 2, 0);
            glTexCoord2f(1, 0);
            glVertex3f(sizeX / 2, sizeY / 2, 0);
        }
        glEnd();
    }
    glPopMatrix();
    return true;
}

bool StateGame::ProcessEvents()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        // Window closed or escape key pressed: exit
        if (event.type == sf::Event::Closed)
        {
            m_window.close();
            break;
        }
        // Space key pressed: play
        if (event.type == sf::Event::KeyPressed)
        {
            //std::cout << "KeyPressed " << (int)event.key.code << std::endl;
            switch (event.key.code)
            {
                case sf::Keyboard::Escape:
                    m_stateManager->PopState();
                    break;
                default:
                    break;
            }
        }
    }
    return true;
}
