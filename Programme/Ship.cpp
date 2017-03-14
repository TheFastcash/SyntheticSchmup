
#include <iostream>

#include "Ship.h"

Ship::Ship(std::string p_name, double p_health, double p_armor, double p_speed, Vector3d p_position, Vector2d p_size)
  : m_name(p_name)
  , m_health(p_health)
  , m_armor(p_armor)
  , m_speed(p_speed)
  , m_position(p_position)
  , m_size(p_size)
{
    // Prepare the ship texture
    if (!m_texture.loadFromFile("resources/ship.png"))
    {
        std::cout << "Cannot load \"resources/ship.png\"" << std::endl;
    }
}

std::string & Ship::Name()
{
    return m_name;
}

double & Ship::Health()
{
    return m_health;
}

double & Ship::Armor()
{
    return m_armor;
}

Vector3d & Ship::Position()
{
    return m_position;
}

Vector2d & Ship::Size()
{
    return m_size;
}

sf::Texture & Ship::Texture()
{
    return m_texture;
}

double & Ship::Speed()
{
    return m_speed;
}

void Ship::Draw()
{
    glPushMatrix();
    {
        double sizeX = m_size.x / 2;
        double sizeY = m_size.y / 2;
        double posX = m_position.x;
        double posY = m_position.y;
        double posZ = m_position.z;
        glColor3d(1, 1, 1);
        sf::Texture::bind(&m_texture);
        glTranslated(posX, posY, posZ);    // Don't put 0.f for 'z' axis, or the square won't be shown
        glBegin(GL_QUADS);                 //draw some squares
        {
            glTexCoord2d(0, 0);
            glVertex3d(-sizeX / 2, sizeY / 2, 0);
            glTexCoord2d(0, 1);
            glVertex3d(-sizeX / 2, -sizeY / 2, 0);
            glTexCoord2d(1, 1);
            glVertex3d(sizeX / 2, -sizeY / 2, 0);
            glTexCoord2d(1, 0);
            glVertex3d(sizeX / 2, sizeY / 2, 0);
        }
        glEnd();
        sf::Texture::bind(NULL);
    }
    glPopMatrix();
}
