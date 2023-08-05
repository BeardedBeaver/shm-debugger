#pragma once

#include "windows.h"

#include "emulator.h"
#include "shm.h"

namespace ACC {

class Emulator : public ::Emulator {
    SMElement m_graphicsACC;
    SMElement m_physicsACC;
    SMElement m_staticACC;

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
