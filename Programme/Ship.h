#pragma once

#include <string>
#include <vector>

//#include "Object2D.h"
#include "Projectile.h"

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class Ship
{
public:
    Ship();

    std::string & Name();
    float & Health();
    float & Armor();
    float & Speed();
    sf::Vector2f & Position();
    sf::Vector2f & Size();
    sf::Texture & Texture();
    std::vector<Projectile> & Projectiles();
    //Object2D & Object2D();

private:
    std::string m_name;
    float m_health;
    float m_armor;
    float m_speed;    // pixels/second
    sf::Vector2f m_position;
    sf::Vector2f m_size;
    sf::Texture m_texture;
    std::vector<Projectile> m_projectiles;
    //Object2D m_object2D;
};
