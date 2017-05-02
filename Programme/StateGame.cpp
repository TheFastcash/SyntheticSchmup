
#include <iostream>

#include "StateGame.h"

StateGame::StateGame(std::shared_ptr<StateManager> p_stateManager,
                     sf::RenderWindow & p_window)
  : IState(p_stateManager, p_window)
  , m_posZGameplay(-15)
  , m_posZBackground(-20)
{
    m_posDestroyObject = instance->GetXYLimits(m_posZGameplay) * 2.;

    double health = 100, armor = 10, speed = 10;
    Vector3d position(0.0, 0.0, m_posZGameplay + 0.001);
    Vector2d size(1.25, 1.1f), hitBoxPosition(0.0, 0.0);
    double hitBoxRadius = 0.3125;
    m_heroShip = new Ship("Ship", health, armor, speed, position, size, hitBoxPosition, hitBoxRadius, &instance->textureMap["ship"]);
    // Initialize scene
    //            ships
    //            enemies
    //
    m_enemyShipList.push_back(Ship("enemy", 100, 10, 5, Vector3d(0.0, 6.0, m_posZGameplay), Vector2d(1.0, 1.0), Vector2d(0.0, 0.0), 0.25, nullptr));
}

bool StateGame::Calculate()
{
    // **** Get elapsed time **** //
    sf::Time elapsedTime = m_clock.getElapsedTime();
    m_clock.restart();

    // **** Update hero ship and its projectiles **** //
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        m_heroShip->Position() += Vector3d(-m_heroShip->Speed() * elapsedTime.asSeconds(), 0, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        m_heroShip->Position() += Vector3d(m_heroShip->Speed() * elapsedTime.asSeconds(), 0, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        m_heroShip->Position() += Vector3d(0, m_heroShip->Speed() * elapsedTime.asSeconds(), 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        m_heroShip->Position() += Vector3d(0, -m_heroShip->Speed() * elapsedTime.asSeconds(), 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        m_heroShip->Shoot();
    }

    /// *********
    /// Temporary
    if (m_enemyShipList.empty())
    {
        m_enemyShipList.push_back(Ship("enemy", 100, 10, 5, Vector3d((double)rand() / (double)RAND_MAX * 20.0 - 10.0, 6.0, m_posZGameplay), Vector2d(1.0, 1.0), Vector2d(0.0, 0.0), 0.25, nullptr));
    }
    /// End temporary
    /// *************

    // **** Update hero projectiles **** //
    UpdateProjectile(elapsedTime, m_heroShip->GetProjectiles());

    // **** Update enemy ships and their projectiles **** //
    for (auto & ship : m_allyShipList)
    {
        UpdateProjectile(elapsedTime, ship.GetProjectiles());
    }

    // **** Update ally ships and their projectiles **** //
    for (auto & ship : m_enemyShipList)
    {
        UpdateProjectile(elapsedTime, ship.GetProjectiles());
    }

    // **** Collisions **** //
    auto & heroShipProjectile = m_heroShip->GetProjectiles();
    for (int i = 0; i < heroShipProjectile.size(); i++)
    {
        for (int j = 0; j < m_enemyShipList.size(); j++)
        {
            if (Drawable::HitBoxCollision(m_enemyShipList[j], heroShipProjectile[i]))
            {
                heroShipProjectile.erase(heroShipProjectile.begin() + i);
                m_enemyShipList.erase(m_enemyShipList.begin() + j);
                i--;
                j--;
                break;    // The the m_enemyShipList loop
            }
        }
    }

    return true;
}

bool StateGame::Draw()
{
    // **** Draw the background **** //
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

    // **** Draw the enemy ships and projectiles **** //
    for (auto & ship : m_enemyShipList)
    {
        for (auto & projectile : ship.GetProjectiles())
        {
            projectile.Draw();
        }
        ship.Draw();
    }

    for (auto & ship : m_allyShipList)
    {
        for (auto & projectile : ship.GetProjectiles())
        {
            projectile.Draw();
        }
        ship.Draw();
    }
    for (auto & projectile : m_heroShip->GetProjectiles())
    {
        projectile.Draw();
    }
    m_heroShip->Draw();

    // Draw debug informations
    m_window.pushGLStates();
    {
        std::string ship_text = std::string("Ship position : ") + "x: " + std::to_string(m_heroShip->Position().x) + "  y: " + std::to_string(m_heroShip->Position().y);
        std::string projectiles_text = std::string("Projectiles quantity : ") + std::to_string(m_heroShip->GetProjectiles().size());
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

void StateGame::UpdateProjectile(sf::Time & elapsedTime, std::vector<Projectile> & projectiles)
{
    size_t size = projectiles.size();
    for (size_t i = 0; i < size; i++)
    {                                                                    //
        projectiles[i].Update(elapsedTime.asMilliseconds());             //   Update the position
        if (projectiles[i].GetPosition().x > m_posDestroyObject.x ||     //   If the projectile is outside 2* the screen
            projectiles[i].GetPosition().x < -m_posDestroyObject.x ||    //
            projectiles[i].GetPosition().y > m_posDestroyObject.y ||     //
            projectiles[i].GetPosition().y < -m_posDestroyObject.y)      //
        {                                                                //
            projectiles.erase(projectiles.begin() + i);                  //     Remove it
            i--;                                                         //     Don't forget to decrease the iterator or the next projectile will not be updated
            size--;
        }
    }
}
