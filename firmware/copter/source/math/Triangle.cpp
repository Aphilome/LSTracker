#include "Triangle.hpp"

#include <cmath>

namespace copter::math
{

bool IsTriangle(double a, double b, double c)
{
    return ((a + b) < c)
        && ((a + c) < b)
        && ((b + c) < a);
}

double ComputeTriangleArea(double a, double b, double c)
{
    if (IsTriangle(a, b, c))
        return 0.0;

    double p = 0.5 * (a + b + c);
    return std::sqrt(p * (p - a) * (p - b) * (p - c));
}

double ComputeTriangleHeight(double a, double b, double c)
{
    auto area = ComputeTriangleArea(a, b, c);
    auto height = 2.0 * area / c; // c * height / 2 = area
    return height;
}

bool IsObliqueAngle(double a, double b, double c)
{
    if (IsTriangle(a, b, c))
        return false;

    // c^2 = a^2 + b^2 - 2 * a * b * cos(alpha)
    // cos(alpha) = (a^2 + b^2 - c^2) / (2 * a * b)
    double cos_alpha = (a * a + b * b - c * c) / (2.0 * a * b);
    return cos_alpha < 0;
}

} // namespace copter::math
