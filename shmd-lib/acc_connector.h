#pragma once

#include "connector.h"

#include "shm.h"
#include "acc_data.h"

namespace ACC {

class Connector : public ::Connector {
    shm acData;

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
