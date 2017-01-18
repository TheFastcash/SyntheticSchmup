#include "Ship.h"

std::string Ship::GetName()
{
    return m_name;
}
double Ship::GetHealth()
{
    return m_health;
}
double Ship::GetArmor()
{
    return m_armor;
}
Object2D Ship::GetObject2D()
{
    return m_object2D;
}
std::vector<Projectile> Ship::GetProjectiles()
{
    return m_projectiles;
}