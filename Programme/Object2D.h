#pragma once

class Object2D
{
public:
    double GetHeight();
    double GetWidth();
    double GetPositionX();
    double GetPositionY();
    double GetDirection();

private:
    double m_height;
    double m_width;
    double m_positionX;
    double m_positionY;
    double m_direction;
};
