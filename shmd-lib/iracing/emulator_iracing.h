#pragma once

#include "emulator.h"

#include "windows.h"

namespace iRacing {

class Emulator : public ::Emulator {
    HANDLE m_fileMappingHandle{};
    HANDLE m_memMapFile{};
    char* m_sharedMem{};
    HANDLE m_dataValidEvent{};

public:
    Emulator() = default;
    ~Emulator() override;

    void initialize() override;
    void update(const std::vector<char>& bytes) override;
    void stop() override;

    Emulator(const Emulator&) = delete;
    Emulator(Emulator&&) = delete;
    Emulator& operator=(const Emulator&) = delete;
    Emulator& operator=(Emulator&&) = delete;
};

}
