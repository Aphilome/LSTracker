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
#include <condition_variable>

namespace copter::tracker
{

using PositionCallback = std::function<void(const geo::Position&)>;

class LocalPositionSystem
{
public:
    ~LocalPositionSystem();

    void UpdateLoop();
    void Stop();

    void SetAlgorithm(std::shared_ptr<ITriangulationAlgorithm> algorithm); // Thread-safe
    void SetPositionCallback(PositionCallback callback); // Not thread-safe, use before UpdateLoop.
    void UpdateAnchor(std::uint8_t id, const geo::Position& position, double distance);

private:
    struct AnchorInfo
    {
        geo::Position position = {};
        double distance = {};
    };

    void ComputePosition(const std::unordered_map<std::uint8_t, AnchorInfo>& anchors);

private:
    std::atomic_bool m_is_working = false;
    PositionCallback m_position_callback = {};

    std::shared_ptr<ITriangulationAlgorithm> m_algorithm;
    std::mutex m_algorithm_mutex;

    std::unordered_map<std::uint8_t, AnchorInfo> m_anchors;
    std::condition_variable m_anchors_cv;
    std::mutex m_anchors_mutex;
    bool m_is_updated = false;
};

} // namespace copter::tracker

#endif