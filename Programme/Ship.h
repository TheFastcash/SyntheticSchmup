#pragma once

#include <string>
#include <vector>

#include "Object2D.h"
#include "Projectile.h"

class Ship
{
public:
    std::string GetName();
    double GetHealth();
    double GetArmor();
    Object2D GetObject2D();
    std::vector<Projectile> GetProjectiles();

private:
    std::string m_name;
    double m_health;
    double m_armor;
    Object2D m_object2D;
    std::vector<Projectile> m_projectiles;
};
