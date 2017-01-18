#pragma once

#include "Object2D.h"

class Projectile
{
public:
    int GetType();
    double GetSpeed();
    double GetDamages();
private:
    int m_type;
    double m_speed;
    double m_damages;
};
