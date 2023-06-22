#pragma once

#include <vector>

class Emulator {
public:
    virtual void initialize() = 0;
    virtual void update(const std::vector<char>& bytes) = 0;
    virtual void stop() = 0;

    virtual ~Emulator() = default;
};
