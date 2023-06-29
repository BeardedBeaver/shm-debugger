#pragma once

#include <chrono>

template <typename Clock>
void defaultSleepFunction(typename Clock::duration duration) {
    auto end = Clock::now() + duration;
    std::this_thread::sleep_for(duration * 0.9);
    while (Clock::now() <= end) {
        // busy-sleep the rest for accuracy
    }
}

class Application {
public:
    Application();

    bool isStopped() const;

    template <typename Callable,
              typename Clock = std::chrono::steady_clock,
              typename ClockFunc = decltype(Clock::now),
              typename SleepFunc = decltype(defaultSleepFunction<Clock>)>
    bool run(Callable callable,
             double frequency,
             ClockFunc clock = Clock::now,
             SleepFunc sleepFunction = defaultSleepFunction<Clock>) {
        auto period = std::chrono::duration_cast<typename Clock::duration>(std::chrono::duration<double>(1.0 / frequency));
        while (true) {
            auto start = clock();
            if (isStopped())
                return false;
            bool shouldBreak = callable();
            if (shouldBreak) {
                return true;
            }
            auto end = clock();
            auto elapsed = end - start;
            if (elapsed < period) {
                sleepFunction(period - elapsed);
            }
        }
    }
};
