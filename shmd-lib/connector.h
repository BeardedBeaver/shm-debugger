#pragma once

#include <array>
#include <vector>

class Connector {
public:
    virtual bool connect(int timeoutMs) = 0;
    virtual void disconnect() = 0;
    virtual std::vector<char> update(int timeoutMs) = 0;
    virtual std::array<char, 4> id() const = 0;

    virtual ~Connector() = default;
};
