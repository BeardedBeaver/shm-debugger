#include <chrono>
#include <iostream>
#include <thread>

#include <boost/program_options.hpp>
#include <fstream>

#include "application.h"
#include "connector_iracing.h"
#include "connector_acc.h"
#include "saver.h"

std::string getCurrentDate() {
    auto now = std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::system_clock::now());
    return std::format("{:%F-%H-%M-%S}", now);
}

int main(int argc, char* argv[]) {
    namespace po = boost::program_options;

    po::options_description desc("Allowed options");

    // clang-format off
    desc.add_options()
        ("help", "Produce help message")
        ("fps", po::value<int>()->default_value(5), "Frames per second [1, 60]");
    // clang-format on

    po::variables_map vm;

    try {
        po::store(po::parse_command_line(argc, argv, desc), vm);
        if (vm.count("help")) {
            std::cout << desc << "\n";
            return 1;
        }
        po::notify(vm);
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
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
        Application app;

        std::vector<std::shared_ptr<Connector>> connectors;
        connectors.reserve(2);

        connectors.push_back(std::make_shared<iRacing::Connector>());
        connectors.push_back(std::make_shared<ACC::Connector>());

        std::shared_ptr<Connector> connector;

        while (!app.isStopped()) {
            std::cout << "Waiting for the connection" << std::endl;
            app.run(
                [&connectors, &connector]() -> bool {
                    for (const auto& c : connectors) {
                        bool result = c->connect(1000); // twice longer than a given fps
                        if (result) {
                            connector = c;
                            std::cout << "Connected to " << std::endl;
                            for (char ch : connector->id()) {
                                std::cout << ch;
                            }
                            std::cout << std::endl;

                            return true;
                        }
                    }
                    return false;
                },
                1);

            if (app.isStopped()) {
                break;
            }

            auto date = getCurrentDate();
            std::string fileName = "shmd_dump_" + date + ".bin";
            std::ofstream stream(fileName, std::ios::binary);
            if (!stream) {
                throw std::ios_base::failure("Failed to open the file " + fileName);
            }
            std::cout << "Dump will be saved to " << fileName << std::endl;
            Saver saver(stream, fps, connector->id());
            std::cout << "Saver started" << std::endl;

            int noDataReceived = 0;

            app.run(
                [&connector, &saver, &noDataReceived, fps]() -> bool {
                    auto data = connector->update(1000 / fps);
                    if (data.empty()) {
                        noDataReceived++;
                        if (noDataReceived > 20) {
                            std::cout << "Source is down, disconnecting" << std::endl;
                            connector->disconnect();
                            return true;
                        }
                    } else {
                        saver.save(data);
                        noDataReceived = 0;
                    }
                    return false;
                },
                fps);
        }
    } catch (std::exception& ex) {
        std::cout << "An error occurred: " << ex.what() << std::endl;
    }

    std::cout << "Dumper thread stopped." << std::endl;
    std::cout << "You can now close this window." << std::endl;

    return 0;
}
