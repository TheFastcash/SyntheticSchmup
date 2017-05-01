
#pragma once

#include "SyntheticSchmup.h"

class Drawable
{
public:
    Drawable(sf::Texture * p_texture)
      : m_texture(p_texture){};
    virtual void Draw() = 0;
    void SetTexture(sf::Texture * p_texture)
    {
        m_texture = p_texture;
    };

    sf::Texture * Texture()
    {
        return m_texture;
    }

protected:
    sf::Texture * m_texture;
};