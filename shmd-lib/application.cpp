#include "application.h"

#include <iostream>
#include <thread>

#include <windows.h>

std::atomic<bool> g_stopFlag(false);

BOOL consoleHandler(DWORD signal) {
    static_assert(std::atomic<bool>::is_always_lock_free);
    if (signal == CTRL_C_EVENT) {
        std::cout << "Ctrl+C detected. Stopping the job. Please wait patiently..." << std::endl;
        g_stopFlag = true;
        return TRUE;
    }
    return FALSE;
}

void defaultSleepFunction(int ms) {
    using namespace std::chrono;

    static double estimate = 5e-3;
    static double mean = 5e-3;
    static double m2 = 0;
    static uint64_t count = 1;

    double seconds = ms / 1000.0;
    while (seconds > estimate) {
        auto start = high_resolution_clock::now();
        std::this_thread::sleep_for(milliseconds(1));
        auto end = high_resolution_clock::now();

        double observed = (end - start).count() / 1e9;
        seconds -= observed;

        ++count;
        double delta = observed - mean;
        mean += delta / count;
        m2 += delta * (observed - mean);
        double stddev = sqrt(m2 / (count - 1));
        estimate = mean + stddev;
    }

    // spin lock
    auto start = high_resolution_clock::now();
    while ((high_resolution_clock::now() - start).count() / 1e9 < seconds)
        ;
}

Application::Application() {
    if (!SetConsoleCtrlHandler(consoleHandler, TRUE)) {
        throw std::runtime_error("Error setting console control handler.");
    }
}

bool Application::isStopped() const {
    return g_stopFlag;
}
