#include "Drawable.h"

bool Drawable::HitBoxCollision(Drawable & A, Drawable & B)
{
    double radiusA = A.GetHitBoxRadius();
    Vector2d posA = A.GetHitBoxPosition();
    double radiusB = B.GetHitBoxRadius();
    Vector2d posB = B.GetHitBoxPosition();

    double x = posA.x - posB.x;
    double y = posA.y - posB.y;
    double distance = sqrt(x * x + y * y);

    return (distance < (radiusA + radiusB));
}