#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>

#include <windows.h>

#include <boost/program_options.hpp>
#include <fstream>

#include "iracing_connector.h"
#include "saver.h"

std::atomic<bool> g_stopFlag(false);

std::string getCurrentDate() {
    auto now = std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::system_clock::now());
    return std::format("{:%F-%H-%M-%S}", now);
}

bool waitForConnection(Connector& connector, int fps) {
    std::cout << "Waiting for the connection" << std::endl;
    while (true) {
        if (g_stopFlag)
            return false;
        bool result = connector.connect(1000 / fps);
        if (result) {
            std::cout << "Connected" << std::endl;
            return true;
        }
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

void doDumping(Connector& connector, int fps) {
    auto date = getCurrentDate();
    std::string fileName = "ir_dump_" + date + ".bin";
    std::ofstream stream(fileName, std::ios::binary);
    if (!stream) {
        throw std::ios_base::failure("Failed to open the file " + fileName);
    }
    std::cout << "Dump will be saved to " << fileName << std::endl;
    Saver saver(stream, fps, connector.id());
    std::cout << "Saver started" << std::endl;
    int noDataReceived = 0;
    while (true) {
        if (g_stopFlag)
            return;
        auto data = connector.update(500 / fps);
        if (data.empty()) {
            noDataReceived++;
            if (noDataReceived > 20) {
                std::cout << "Source is down, disconnecting" << std::endl;
                connector.disconnect();
                return;
            }
        } else {
            saver.save(data);
            noDataReceived = 0;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / fps));
    }
}

void backgroundJob(Connector& connector, int fps) {
    while (true) {
        if (g_stopFlag)
            break;
        bool result = waitForConnection(connector, fps);
        if (!result) {
            continue;
        }
        doDumping(connector, fps);
    }
}

BOOL consoleHandler(DWORD signal) {
    if (signal == CTRL_C_EVENT) {
        std::cout << "Ctrl+C detected. Stopping the job. Please wait patiently..." << std::endl;
        g_stopFlag = true;
        return TRUE;
    }
    return FALSE;
}

int main(int argc, char* argv[]) {
    if (!SetConsoleCtrlHandler(consoleHandler, TRUE)) {
        std::cerr << "Error setting console control handler." << std::endl;
        return 1;
    }

    namespace po = boost::program_options;

    po::options_description desc("Allowed options");
    desc.add_options()("help", "Produce help message")("fps", po::value<int>()->default_value(5), "Frames per second");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 1;
    }

    int fps = vm["fps"].as<int>();
    if (fps < 1 || fps > 60) {
        std::cout << "Invalid fps value: " << fps << std::endl;
        std::cout << "Accepted values are [1, 60]" << std::endl;
        return 1;
    }
    std::cout << "Frames per second: " << fps << std::endl;

    try {
        std::thread bgThread([fps]() {
            iRacing::Connector connector;
            backgroundJob(connector, fps);
        });
        bgThread.join();
    } catch (std::exception& ex) {
        std::cout << "An error occurred: " << ex.what() << std::endl;
    }

    std::cout << "Dumper thread stopped." << std::endl;
    std::cout << "You can now close this window." << std::endl;

    return 0;
}
