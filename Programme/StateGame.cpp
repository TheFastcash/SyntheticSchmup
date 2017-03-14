
#include <iostream>

#include "StateGame.h"

StateGame::StateGame(std::shared_ptr<StateManager> p_stateManager,
                     sf::RenderWindow & p_window)
  : IState(p_stateManager, p_window)
  , m_posZGameplay(-15)
  , m_posZBackground(-20)
  , m_ship("Ship", 100, 10, 10, Vector3d(0, 0, m_posZGameplay), Vector2d(5, 4.4f))
{
    m_posDestroyObject = instance->GetXYLimits(m_posZGameplay) * 2.;
    // Initialize scene
    //            ships
    //            enemies
    //
}

bool StateGame::Calculate()
{
    sf::Time timeSpent = m_clock.getElapsedTime();
    m_clock.restart();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        m_ship.Position() += Vector3d(-m_ship.Speed() * timeSpent.asSeconds(), 0, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        m_ship.Position() += Vector3d(m_ship.Speed() * timeSpent.asSeconds(), 0, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        m_ship.Position() += Vector3d(0, m_ship.Speed() * timeSpent.asSeconds(), 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        m_ship.Position() += Vector3d(0, -m_ship.Speed() * timeSpent.asSeconds(), 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        m_projectiles.push_back(Projectile(Projectile::Group::Ally, Projectile::Type::Normal, Vector2d(0.4, 0.8), m_ship.Position(), 5, -M_PI / 9, 2.0));
        m_projectiles.push_back(Projectile(Projectile::Group::Ally, Projectile::Type::Normal, Vector2d(0.4, 0.8), m_ship.Position(), 5, 0, 2.0));
        m_projectiles.push_back(Projectile(Projectile::Group::Ally, Projectile::Type::Normal, Vector2d(0.4, 0.8), m_ship.Position(), 5, M_PI / 9, 2.0));
    }

    for (size_t i = 0; i < m_projectiles.size(); i++)                      // For each projectile
    {                                                                      //
        m_projectiles[i].Update(timeSpent.asMilliseconds());               //   Update the position
        if (m_projectiles[i].GetPosition().x > m_posDestroyObject.x ||     //   If the projectile is outside 2* the screen
            m_projectiles[i].GetPosition().x < -m_posDestroyObject.x ||    //
            m_projectiles[i].GetPosition().y > m_posDestroyObject.y ||     //
            m_projectiles[i].GetPosition().y < -m_posDestroyObject.y)      //
        {                                                                  //
            m_projectiles.erase(m_projectiles.begin() + i);                //     Remove it
            i--;                                                           //     Don't forget to decrease the iterator or the next projectile will not be updated
        }
    }
    return true;
}

bool StateGame::Draw()
{
    // Draw the background
    glPushMatrix();
    {
        //sf::Texture::bind(&m_backgroundTexture);
        glTranslated(0., 0., m_posZBackground);    // Don't put 0.f for 'z' axis, or the square won't be shown
        //glRotatef(25.f, 1.f, 0.f, 0.f);
        glBegin(GL_QUADS);    //draw some squares
        {
            glColor3d(0, 0.2, 0.7);
            glVertex3d(-1, 1, 0);
            glColor3d(0.2, 0.7, 0);
            glVertex3d(-1, -1, 0);
            glColor3d(0.7, 0, 0.2);
            glVertex3d(1, -1, 0);
            glColor3d(1, 1, 1);
            glVertex3d(1, 1, 0);
        }
        glEnd();
    }
    glPopMatrix();

    // Draw the projectiles
    for (size_t i = 0; i < m_projectiles.size(); i++)
    {
        m_projectiles[i].Draw();
    }

    // Draw the ship
    m_ship.Draw();

    // Draw debug informations
    m_window.pushGLStates();
    {
        std::string ship_text = std::string("Ship position : ") + "x: " + std::to_string(m_ship.Position().x) + "  y: " + std::to_string(m_ship.Position().y);
        std::string projectiles_text = std::string("Projectiles quantity : ") + std::to_string(m_projectiles.size());
        auto ship_sfText = sf::Text(ship_text, instance->font, 11);
        auto projectiles_sfText = sf::Text(projectiles_text, instance->font, 11);
        ship_sfText.setPosition(10, 10);
        projectiles_sfText.setPosition(10, 22);
        m_window.draw(ship_sfText);
        m_window.draw(projectiles_sfText);
    }
    m_window.popGLStates();

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
