#include "LocalPositionSystem.hpp"

#include "geo/WGS84.hpp"

#include <thread>

namespace copter::tracker
{

LocalPositionSystem::~LocalPositionSystem()
{
    Stop();
}

void LocalPositionSystem::UpdateLoop(std::uint32_t sleep_us)
{
    m_is_working = true;

    while (m_is_working)
    {
        ComputePosition();
        std::this_thread::sleep_for(std::chrono::microseconds(sleep_us));
    }
}

void LocalPositionSystem::Stop()
{
    m_is_working = false;
}

void LocalPositionSystem::UpdateAnchor(const std::string& name)
{
}

void LocalPositionSystem::SetPositionCallback(PositionCallback callback)
{
    m_position_callback = std::move(callback);
}

void LocalPositionSystem::ComputePosition()
{
    auto point = m_algorithm.Execute({});
    if (point && m_position_callback)
    {
        auto geo_position = geo::ConvertToGeoPosition(point.value());
        m_position_callback(geo_position);
    }
}

} // namespace copter::tracker
