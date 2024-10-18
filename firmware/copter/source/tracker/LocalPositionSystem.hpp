#ifndef LOCAL_POSITION_SYSTEM_HPP
#define LOCAL_POSITION_SYSTEM_HPP

#include <string>

namespace copter::tracker
{

class LocalPositionSystem
{
public:
    void UpdateAnchor(const std::string& name);
};

} // namespace copter::tracker

#endif