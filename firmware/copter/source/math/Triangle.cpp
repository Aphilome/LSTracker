#include "Triangle.hpp"

#include <cmath>

namespace copter::math
{

double ComputeTriangleArea(double a, double b, double c)
{
    double p = 0.5 * (a + b + c);
    return std::sqrt(p * (p - a) * (p - b) * (p - c));
}

bool IsObliqueAngle(double a, double b, double c)
{
    // c^2 = a^2 + b^2 - 2 * a * b * cos(alpha)
    // cos(alpha) = (a^2 + b^2 - c^2) / (2 * a * b)
    double cos_alpha = (a * a + b * b - c * c) / (2.0 * a * b);
    return cos_alpha < 0;
}

} // namespace copter::math
