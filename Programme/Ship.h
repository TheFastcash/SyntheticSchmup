#pragma once

#include <string>
#include <vector>

#include "Drawable.h"
#include "Projectile.h"
#include "SyntheticSchmup.h"

class Ship : public Drawable
{
public:
    Ship(std::string name, double health, double armor, double speed, Vector3d position, Vector2d size, sf::Texture * p_texture);

    std::string & Name();
    double & Health();
    double & Armor();
    double & Speed();
    Vector3d & Position();
    Vector2d & Size();
    void Shoot();
    std::vector<Projectile> & GetProjectiles();
    virtual void Draw() override;

private:
    std::string m_name;
    double m_health;
    double m_armor;
    double m_speed;    // pixels/second
    Vector3d m_position;
    Vector2d m_size;
    std::vector<Projectile> m_projectiles;
};
