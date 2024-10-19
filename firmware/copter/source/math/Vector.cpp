#include "Vector.hpp"

#include <cmath>

namespace copter::math
{

double Vector::GetLength() const
{
    return std::sqrt(x * x + y * y + z *z);
}

void Vector::Normalize()
{
    auto length = GetLength();
    x /= length;
    y /= length;
    z /= length;
}

} // namespace copter::math
