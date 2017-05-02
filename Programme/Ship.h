#pragma once

#include <string>
#include <vector>

#include "Drawable.h"
#include "Projectile.h"
#include "SyntheticSchmup.h"

class Ship : public Drawable
{
public:
    Ship(std::string name, double health, double armor, double speed, Vector3d position, Vector2d size, Vector2d hitBoxPosition, double hitBoxRadius, sf::Texture * p_texture);

    std::string & Name();
    double & Health();
    double & Armor();
    double & Speed();
    Vector3d & Position();
    Vector2d & Size();
    virtual Vector2d GetHitBoxPosition() override;
    virtual double GetHitBoxRadius() override;
    void Shoot();
    std::vector<Projectile> & GetProjectiles();
    virtual void Draw() override;

private:
    std::string m_name;
    double m_health;
    double m_armor;
    double m_speed;    // pixels/second
    Vector3d m_position;
    Vector2d m_size, m_hitBoxPosition;
    double m_hitBoxRadius;
    std::vector<Projectile> m_projectiles;
    sf::Clock m_lastTimeShoot;

    double red, green, blue;    // TODO Remove when we have a texture, it is just for fun
};
