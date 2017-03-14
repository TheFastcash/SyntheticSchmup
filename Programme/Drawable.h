
#pragma once

#include "SyntheticSchmup.h"

class Drawable
{
public:
    Drawable(){};
    virtual void Draw() = 0;
    void SetTexture(sf::Texture texture)
    {
        m_texture = texture;
    };

protected:
    sf::Texture m_texture;
};