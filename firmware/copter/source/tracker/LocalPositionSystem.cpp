#include "LocalPositionSystem.hpp"

#include "geo/WGS84.hpp"

#include <thread>

namespace copter::tracker
{

LocalPositionSystem::~LocalPositionSystem()
{
    Stop();
}

void LocalPositionSystem::UpdateLoop()
{
    m_is_working = true;

    while (m_is_working)
    {
        std::unique_lock guard(m_anchors_mutex);
        m_anchors_cv.wait(guard, [this] { return !m_is_working || !m_is_updated; });

        if (!m_is_working)
            break;

        auto current_anchors = m_anchors;
        m_is_updated = true;
        guard.unlock();

        ComputePosition(current_anchors);
    }
}

void LocalPositionSystem::Stop()
{
    m_is_working = false;
    m_anchors_cv.notify_all();
}

void LocalPositionSystem::UpdateAnchor(std::uint8_t id, const geo::Position& position, double distance)
{
    {
        std::lock_guard guard(m_anchors_mutex);

        auto& anchor = m_anchors[id];
        anchor.position = position;
        anchor.distance = distance;

        m_is_updated = false;
    }
    m_anchors_cv.notify_all();
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

void LocalPositionSystem::ComputePosition(const std::unordered_map<std::uint8_t, AnchorInfo>& anchors)
{
    std::shared_ptr<ITriangulationAlgorithm> current_algorithm;
    {
        std::lock_guard guard(m_algorithm_mutex);
        current_algorithm = m_algorithm;
    }

    std::vector<math::Sphere> spheres;
    spheres.reserve(anchors.size());

    for (auto& [_, anchor] : anchors)
    {
        auto& sphere = spheres.emplace_back();
        sphere.center = geo::ConvertToCartesian(anchor.position);
        sphere.radius = anchor.distance;
    }

    auto result = current_algorithm->Execute(spheres);
    if (result.first && m_position_callback)
    {
        auto geo_position = geo::ConvertToGeoPosition(result.first.value());
        if (result.second)
        {
            auto second_geo_position = geo::ConvertToGeoPosition(result.second.value());
            if (second_geo_position.altitude_m < geo_position.altitude_m)
            {
                geo_position = second_geo_position;
            }
        }
        m_position_callback(geo_position);
    }
}

} // namespace copter::tracker
