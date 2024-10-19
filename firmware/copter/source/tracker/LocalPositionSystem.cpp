#include "LocalPositionSystem.hpp"

namespace copter::tracker
{

LocalPositionSystem::~LocalPositionSystem()
{
    Stop();
}

void LocalPositionSystem::UpdateThread()
{
    m_is_working = true;

    while (m_is_working)
    {
        ComputePosition();
    }
}

void LocalPositionSystem::Stop()
{
    m_is_working = false;
}

void LocalPositionSystem::UpdateAnchor(const std::string& name)
{
}

std::optional<geo::Position> LocalPositionSystem::GetPosition() const
{
    std::lock_guard guard(m_position_mutex);
    return m_position;
}

void LocalPositionSystem::ComputePosition()
{
    auto position = m_algorithm.Execute({});
}

} // namespace copter::tracker
