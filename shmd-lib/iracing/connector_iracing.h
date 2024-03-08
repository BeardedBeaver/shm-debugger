#pragma once

#include <memory>

#include "connector.h"

namespace iRacing {
class Connector : public ::Connector {
    int rawDataLength{};
    int sessionInfoUpdate{};
    std::unique_ptr<char[]> rawData{};

public:
    Connector() = default;

    bool connect(int timeoutMs) override;
    void disconnect() override;
    std::vector<char> update(int timeoutMs) override;
    [[nodiscard]] std::array<char, 4> id() const override;

    Connector(const Connector&) = delete;
    Connector(Connector&&) = delete;
    Connector& operator=(const Connector&) = delete;
    Connector& operator=(Connector&&) = delete;
};

}
