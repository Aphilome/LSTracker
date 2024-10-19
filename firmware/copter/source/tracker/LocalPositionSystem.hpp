#ifndef LOCAL_POSITION_SYSTEM_HPP
#define LOCAL_POSITION_SYSTEM_HPP

#include "TriangulationAlgorithm.hpp"

#include "geo/Position.hpp"

#include <atomic>
#include <string>
#include <cstdint>
#include <functional>

namespace copter::tracker
{

using PositionCallback = std::function<void(const geo::Position&)>;

class LocalPositionSystem
{
public:
    ~LocalPositionSystem();

    void UpdateLoop(std::uint32_t sleep_us = 10'000);
    void Stop();

    void SetPositionCallback(PositionCallback callback);
    void UpdateAnchor(const std::string& name);

private:
    void ComputePosition();

private:
    std::atomic_bool m_is_working = false;
    PositionCallback m_position_callback = {};
    TriangulationAlgorithm m_algorithm;
};

} // namespace copter::tracker

#endif