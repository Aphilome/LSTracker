#ifndef LOCAL_POSITION_SYSTEM_HPP
#define LOCAL_POSITION_SYSTEM_HPP

#include "TriangulationAlgorithm.hpp"

#include "geo/Position.hpp"

#include <mutex>
#include <atomic>
#include <string>
#include <optional>

namespace copter::tracker
{

class LocalPositionSystem
{
public:
    ~LocalPositionSystem();

    void UpdateThread();
    void Stop();

    void UpdateAnchor(const std::string& name);
    std::optional<geo::Position> GetPosition() const;

private:
    void ComputePosition();

private:
    std::atomic_bool m_is_working = false;
    
    TriangulationAlgorithm m_algorithm;

    std::optional<geo::Position> m_position;
    mutable std::mutex m_position_mutex;
};

} // namespace copter::tracker

#endif