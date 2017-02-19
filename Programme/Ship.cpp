
#include <iostream>

#include "Ship.h"

Ship::Ship()
  : m_name("ship")
  , m_health(100)
  , m_armor(10)
  , m_speed(10)
  , m_position(0, 0)
  , m_size(5, 4.4f)
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

float & Ship::Health()
{
    return m_health;
}

float & Ship::Armor()
{
    return m_armor;
}

//Object2D & Ship::Object2D()
//{
//    return m_object2D;
//}

std::vector<Projectile> & Ship::Projectiles()
{
    return m_projectiles;
}

sf::Vector2f & Ship::Position()
{
    return m_position;
}

sf::Vector2f & Ship::Size()
{
    return m_size;
}

sf::Texture & Ship::Texture()
{
    return m_texture;
}

float & Ship::Speed()
{
    return m_speed;
}
