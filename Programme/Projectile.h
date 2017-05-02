#pragma once

#include "Drawable.h"
#include "Object2D.h"
#include "SyntheticSchmup.h"

class Projectile : public Drawable
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

    Projectile(Group group, Type type, Vector3d position, Vector2d size, Vector2d hitBoxPosition, double hitBoxRadius, double speed, double angle, double damages, sf::Texture * p_texture);
    Type GetType();
    Group GetGroup();
    Vector3d GetPosition();
    virtual Vector2d GetHitBoxPosition() override;
    virtual double GetHitBoxRadius() override;
    double GetDamages();
    void Update(const sf::Int32 & milliseconds);
    virtual void Draw() override;

private:
    Group m_group;
    Type m_type;
    Vector3d m_position;
    Vector2d m_size, m_hitBoxPosition;
    double m_hitBoxRadius;
    double m_speed;
    double m_angle;
    double m_damages;
    double red, green, blue;    // TODO Remove when we have a texture, it is just for fun
};
