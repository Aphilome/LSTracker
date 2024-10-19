#ifndef LOCAL_POSITION_SYSTEM_HPP
#define LOCAL_POSITION_SYSTEM_HPP

#include "ITriangulationAlgorithm.hpp"

#include "geo/Position.hpp"

#include <mutex>
#include <atomic>
#include <memory>
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

    void SetAlgorithm(std::shared_ptr<ITriangulationAlgorithm> algorithm); // Thread-safe
    void SetPositionCallback(PositionCallback callback); // Not thread-safe, use before UpdateLoop.
    void UpdateAnchor(const std::string& name);

private:
    void ComputePosition();

private:
    std::atomic_bool m_is_working = false;
    PositionCallback m_position_callback = {};

    std::shared_ptr<ITriangulationAlgorithm> m_algorithm;
    std::mutex m_algorithm_mutex;
};

} // namespace copter::tracker

#endif