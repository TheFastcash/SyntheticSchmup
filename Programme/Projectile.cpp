
#include "Projectile.h"

Projectile::Projectile(Group p_group, Type p_type, Vector2d p_size, Vector3d p_position, double p_speed, double p_angle, double p_damages, sf::Texture * p_texture)
  : m_group(p_group)
  , m_type(p_type)
  , m_size(p_size)
  , m_position(p_position)
  , m_speed(p_speed)
  , m_angle(p_angle)
  , m_damages(p_damages)
  , Drawable(p_texture)
{
    red = (double)rand() / (double)RAND_MAX;
    green = (double)rand() / (double)RAND_MAX;
    blue = (double)rand() / (double)RAND_MAX;

    instance->soundMap.at("shot").Play();
}

Projectile::Type Projectile::GetType()
{
    return m_type;
}

Projectile::Group Projectile::GetGroup()
{
    return m_group;
}

Vector3d Projectile::GetPosition()
{
    return m_position;
}
double Projectile::GetDamages()
{
    return m_damages;
}

void Projectile::Update(const sf::Int32 & milliseconds)
{
    double x = m_speed * cos(m_angle + M_PI_2) / milliseconds;
    double y = m_speed * sin(-m_angle + M_PI_2) / milliseconds;
    m_position += Vector3d(x, y, 0);
}

void Projectile::Draw()
{
    glPushMatrix();
    {
        double sizeX = m_size.x / 2;
        double sizeY = m_size.y / 2;
        double posX = m_position.x;
        double posY = m_position.y;
        double posZ = m_position.z;
        //sf::Texture::bind(&m_texture);
        glColor3d(red, green, blue);
        glTranslated(posX, posY, posZ);    // Don't put 0.f for 'z' axis, or the square won't be shown
        glRotated(m_angle * 180 / M_PI, 0, 0, 1);
        glBegin(GL_QUADS);    //draw some squares
        {
            //glTexCoord2d(0, 0);
            glVertex3d(-sizeX / 2, sizeY / 2, 0);
            //glTexCoord2d(0, 1);
            glVertex3d(-sizeX / 2, -sizeY / 2, 0);
            //glTexCoord2d(1, 1);
            glVertex3d(sizeX / 2, -sizeY / 2, 0);
            //glTexCoord2d(1, 0);
            glVertex3d(sizeX / 2, sizeY / 2, 0);
        }
        glEnd();
        glColor3d(1, 1, 1);
    }
    glPopMatrix();
}
