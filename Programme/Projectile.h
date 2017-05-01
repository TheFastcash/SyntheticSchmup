#pragma once

#include "Drawable.h"
#include "Object2D.h"
#include "SyntheticSchmup.h"

class Projectile : Drawable
{
public:
    enum class Group
    {    // TODO Find another name
        Ally,
        Ennemy
    };

    enum class Type
    {    // Define the shape and the texture. These will probably be separated in the future
        Normal,
        Ball
    };

    Projectile(Group group, Type type, Vector2d size, Vector3d position, double speed, double angle, double damages, sf::Texture * p_texture);
    Type GetType();
    Group GetGroup();
    Vector3d GetPosition();
    double GetDamages();
    void Update(const sf::Int32 & milliseconds);
    virtual void Draw() override;

private:
    Group m_group;
    Type m_type;
    Vector2d m_size;
    Vector3d m_position;
    double m_speed;
    double m_angle;
    double m_damages;
    double red, green, blue;    // TODO Remove when we have a texture, it is just for fun
};
