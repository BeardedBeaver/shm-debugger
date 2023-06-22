#pragma once

#include <vector>

class Connector {
public:
    virtual bool connect(int timeoutMs) = 0;
    virtual void disconnect() = 0;
    virtual std::vector<char> update(int timeoutMs) = 0;

    virtual ~Connector() = default;
};