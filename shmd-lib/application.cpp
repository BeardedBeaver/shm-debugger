#include "application.h"

#include <iostream>

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

Application::Application() {
    if (!SetConsoleCtrlHandler(consoleHandler, TRUE)) {
        throw std::runtime_error("Error setting console control handler.");
    }
}

bool Application::isStopped() const {
    return g_stopFlag;
}
