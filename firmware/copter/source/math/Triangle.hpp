#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

namespace copter::math
{

// Cheks if the triangle with given edges is exist
bool IsTriangle(double a, double b, double c);

// The area of the triangle Heron's formula.
double ComputeTriangleArea(double a, double b, double c);

// Returns the height to the edge c.
double ComputeTriangleHeight(double a, double b, double c);

// Determines if the angle between a and b in triangle is oblique.
bool IsObliqueAngle(double a, double b, double c);

} // namespace copter::math

#endif