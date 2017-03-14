#pragma once

#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

typedef sf::Vector2<double> Vector2d;
typedef sf::Vector3<double> Vector3d;

class SyntheticSchmup
{
public:
    static SyntheticSchmup * Get();

    void ExitWithMessage(int p_error, std::string p_message = "No message");

    void Initialize(int p_width, int p_height, double p_fov);
    Vector2d GetXYLimits(double depth);

    int windowWidth;
    int windowHeight;
    double windowRatio;
    double windowFov;
    sf::Font font;

private:
    static SyntheticSchmup m_instance;
    SyntheticSchmup(){};
    ~SyntheticSchmup(){};
};

extern SyntheticSchmup * instance;
