#include "Position.hpp"

#include "WGS84.hpp"

namespace copter::geo
{

double Position::GetDistance(const Position& other) const
{
    auto this_point = ConvertToCartesian(*this);
    auto other_point = ConvertToCartesian(other);
    return this_point.GetDistance(other_point);
}

} // namespace copter::geo
