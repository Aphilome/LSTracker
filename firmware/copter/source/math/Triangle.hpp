#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

namespace copter::math
{

// The area of the triangle Heron's formula.
double ComputeTriangleArea(double a, double b, double c);

// Determines if the angle between a and b in triangle is oblique.
bool IsObliqueAngle(double a, double b, double c);

} // namespace copter::math

#endif