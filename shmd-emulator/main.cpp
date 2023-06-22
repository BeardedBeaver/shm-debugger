#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <fstream>

#include <windows.h>

#include <boost/program_options.hpp>

#include "loader.h"
#include "iracing_emulator.h"

std::atomic<bool> g_stopFlag(false);

BOOL consoleHandler(DWORD signal) {
    static_assert(std::atomic<bool>::is_always_lock_free);
    if (signal == CTRL_C_EVENT) {
        std::cout << "Ctrl+C detected. Stopping the job. Please wait patiently..." <<
                  std::endl;
        g_stopFlag = true;
        return TRUE;
    }
    return FALSE;
}

void backgroundJob(Emulator &emulator, Loader &loader, int fps) {
    std::cout << "Press Ctrl+C to stop the tool" << std::endl;
    while (true) {
        if (g_stopFlag)
            break;
        auto data = loader.load();
        if (data.empty()) {
            std::cout << "Emulator reached end of file" << std::endl;
            break;
        }
        emulator.update(data);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / fps));
    }
}

int main(int argc, char *argv[]) {
    if (!SetConsoleCtrlHandler(consoleHandler, TRUE)) {
        std::cerr << "Error setting console control handler." << std::endl;
        return 1;
    }

    namespace po = boost::program_options;
    std::string inputFileName;

    po::options_description desc("Allowed options");
    desc.add_options()
            ("help", "Produce help message")
            ("input-file", po::value<std::string>(&inputFileName)->required(), "Input file name");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 1;
    }

    try {
        po::notify(vm);
    }
    catch (const std::exception &ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }

    try {
        std::thread bgThread([&inputFileName]() {
            std::ifstream stream(inputFileName, std::ios::binary);
            Loader loader(stream);
            iRacing::Emulator emulator;
            emulator.initialize();
            int fps = loader.getFps();
            std::cout << "Frames per second: " << fps << std::endl;

            backgroundJob(emulator, loader, fps);

        });
        bgThread.join();
    }
    catch (std::exception &ex) {
        std::cout << "An error occurred: " << ex.what() << std::endl;
    }

    std::cout << "Emulator thread stopped." << std::endl;
    std::cout << "You can now close this window." << std::endl;

    return 0;
}