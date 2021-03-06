#ifndef STOPWATCH_HPP_NM8GXRNS
#define STOPWATCH_HPP_NM8GXRNS

#include <chrono>

template <typename TimeT = std::chrono::milliseconds, typename ClockT = std::chrono::high_resolution_clock,
    typename DurationT = double>
class Stopwatch {
private:
    std::chrono::time_point<ClockT> _start, _end;

public:
    Stopwatch() { start(); }
    void start() { _start = _end = ClockT::now(); }
    DurationT elapsed()
    {
        _end = ClockT::now();
        auto delta = std::chrono::duration_cast<TimeT>(_end - _start);
        return delta.count();
    }
};

#endif /* end of include guard: STOPWATCH_HPP_NM8GXRNS */
