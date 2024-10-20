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

void LocalPositionSystem::SetAlgorithm(std::shared_ptr<ITriangulationAlgorithm> algorithm)
{
    std::lock_guard guard(m_algorithm_mutex);
    m_algorithm = std::move(algorithm);
}

void LocalPositionSystem::SetPositionCallback(PositionCallback callback)
{
    m_position_callback = std::move(callback);
}

void LocalPositionSystem::ComputePosition()
{
    std::shared_ptr<ITriangulationAlgorithm> current_algorithm;
    {
        std::lock_guard guard(m_algorithm_mutex);
        current_algorithm = m_algorithm;
    }

    math::Sphere first = { math::Point{ 0.0, 0.0, 0.0 }, 65.0 };
    math::Sphere second = { math::Point{ 100.0, 0.0, 0.0 }, 38.0 };
    math::Sphere third = { math::Point{ 60.0, 50.0, 0.0 }, 49.0 };
    auto point = current_algorithm->Execute({ first, second, third });

    if (point && m_position_callback)
    {
        auto geo_position = geo::ConvertToGeoPosition(point.value());
        m_position_callback(geo_position);
    }
}

} // namespace copter::tracker
