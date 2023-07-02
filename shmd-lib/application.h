#pragma once

#include <chrono>

void defaultSleepFunction(int ms);

class Application {
public:
    Application();

    bool isStopped() const;

    template <typename Callable,
              typename Clock = std::chrono::steady_clock,
              typename ClockFunc = decltype(Clock::now),
              typename SleepFunc = decltype(defaultSleepFunction)>
    bool run(Callable callable,
             double frequency,
             ClockFunc clock = Clock::now,
             SleepFunc sleepFunction = defaultSleepFunction) {
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
                sleepFunction(std::chrono::duration_cast<std::chrono::milliseconds>(period - elapsed).count());
            }
        }
    }
};
