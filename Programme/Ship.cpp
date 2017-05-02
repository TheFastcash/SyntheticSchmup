
#include <iostream>

#include "Ship.h"

Ship::Ship(std::string p_name, double p_health, double p_armor, double p_speed, Vector3d p_position, Vector2d p_size, Vector2d p_hitBoxPosition, double p_hitBoxRadius, sf::Texture * p_texture)
  : m_name(p_name)
  , m_health(p_health)
  , m_armor(p_armor)
  , m_speed(p_speed)
  , m_position(p_position)
  , m_size(p_size)
  , m_hitBoxPosition(p_hitBoxPosition)
  , m_hitBoxRadius(p_hitBoxRadius)
  , Drawable(p_texture)
{
    red = (double)rand() / (double)RAND_MAX;
    green = (double)rand() / (double)RAND_MAX;
    blue = (double)rand() / (double)RAND_MAX;

    m_lastTimeShoot.restart();
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

Vector2d Ship::GetHitBoxPosition()
{
    return Vector2d(m_position.x + m_hitBoxPosition.x, m_position.y + m_hitBoxPosition.y);
}

double Ship::GetHitBoxRadius()
{
    return m_hitBoxRadius;
}

double & Ship::Speed()
{
    return m_speed;
}

void Ship::Shoot()
{
    if (m_lastTimeShoot.getElapsedTime().asMilliseconds() > 200)
    {
        Vector2d size(0.1, 0.2), position(0.0, 0.0);
        double radius = 0.05, speed = 3.0, damages = 2.0;
        m_projectiles.push_back(Projectile(Projectile::Group::Ally, Projectile::Type::Normal, m_position, size, position, radius, speed, -M_PI / 9, damages, new sf::Texture()));
        m_projectiles.push_back(Projectile(Projectile::Group::Ally, Projectile::Type::Normal, m_position, size, position, radius, speed, 0, damages, new sf::Texture()));
        m_projectiles.push_back(Projectile(Projectile::Group::Ally, Projectile::Type::Normal, m_position, size, position, radius, speed, M_PI / 9, damages, new sf::Texture()));
        m_lastTimeShoot.restart();
    }
}

std::vector<Projectile> & Ship::GetProjectiles()
{
    return m_projectiles;
}

void Ship::Draw()
{
    if (m_texture != nullptr)
    {
        glPushMatrix();
        {
            double sizeX = m_size.x / 2;
            double sizeY = m_size.y / 2;
            double posX = m_position.x;
            double posY = m_position.y;
            double posZ = m_position.z;
            glColor3d(1, 1, 1);
            sf::Texture::bind(m_texture);
            glTranslated(posX, posY, posZ);    // Don't put 0.f for 'z' axis, or the square won't be shown
            glBegin(GL_QUADS);                 //draw some squares
            {
                glTexCoord2d(0, 0);
                glVertex3d(-sizeX, sizeY, 0);
                glTexCoord2d(0, 1);
                glVertex3d(-sizeX, -sizeY, 0);
                glTexCoord2d(1, 1);
                glVertex3d(sizeX, -sizeY, 0);
                glTexCoord2d(1, 0);
                glVertex3d(sizeX, sizeY, 0);
            }
            glEnd();
            sf::Texture::bind(NULL);
        }
        glPopMatrix();
    }
    else
    {
        glPushMatrix();
        {
            double sizeX = m_size.x / 2;
            double sizeY = m_size.y / 2;
            double posX = m_position.x;
            double posY = m_position.y;
            double posZ = m_position.z;
            glColor3d(red, green, blue);
            glTranslated(posX, posY, posZ);    // Don't put 0.f for 'z' axis, or the square won't be shown
            glBegin(GL_QUADS);                 //draw some squares
            {
                glVertex3d(-sizeX, sizeY, 0);
                glVertex3d(-sizeX, -sizeY, 0);
                glVertex3d(sizeX, -sizeY, 0);
                glVertex3d(sizeX, sizeY, 0);
            }
            glEnd();
            sf::Texture::bind(NULL);
        }
        glPopMatrix();
    }

    // Draw the hitbox
    glPushMatrix();
    {
        double radius = m_hitBoxRadius;
        double posX = m_position.x + m_hitBoxPosition.x;
        double posY = m_position.y + m_hitBoxPosition.y;
        double posZ = m_position.z + 0.001;
        glColor3d(1.0 - red, 1.0 - green, 1.0 - blue);
        glTranslated(posX, posY, posZ);    // Don't put 0.f for 'z' axis, or the square won't be shown
        glBegin(GL_POLYGON);               //draw some squares
        {
            int nbrOfPoints = 20;
            double pi2point = 2 * M_PI / nbrOfPoints;
            for (int i = 0; i < nbrOfPoints; i++)
            {
                double v = pi2point * i;
                glVertex3d(cos(v) * radius, sin(v) * radius, 0);
            }
        }
        glEnd();
        sf::Texture::bind(NULL);
    }
    glPopMatrix();
}
