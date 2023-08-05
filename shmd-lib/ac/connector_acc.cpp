#include "connector_acc.h"

namespace ACC {

bool Connector::connect(int timeoutMs) {
    int res1 = acData.initGraphicsACC();
    int res2 = acData.initPhysicsACC();
    int res3 = acData.initStaticACC();

    auto cleanup = [&]() {
        dismiss(acData.m_graphicsACC);
        dismiss(acData.m_physicsACC);
        dismiss(acData.m_staticACC);
    };

    if (res1 == 0 && res2 == 0 && res3 == 0) {
        // check if AC is active and skip for now
        auto statics = *((SPageFileStaticACC*)acData.m_graphicsACC.mapFileBuffer);
        if (wcscmp(statics.playerName, statics.playerSurname) != 0) {
            auto pg = (SPageFileGraphicAC*)acData.m_graphicsACC.mapFileBuffer;
            if (pg->status == AC_OFF) {
                cleanup();
                return false;
            }
            return true;
        }
    }
    cleanup();
    return false;
}

void Connector::disconnect() {
    dismiss(acData.m_graphicsACC);
    dismiss(acData.m_physicsACC);
    dismiss(acData.m_staticACC);
}

std::vector<char> Connector::update(int timeoutMs) {
    Data data;
    data.graphics = *((SPageFileGraphicACC*)acData.m_staticACC.mapFileBuffer);
    data.physics = *((SPageFilePhysicsACC*)acData.m_graphicsACC.mapFileBuffer);
    data.statics = *((SPageFileStaticACC*)acData.m_physicsACC.mapFileBuffer);

    return serializeData(data);
}

std::array<char, 4> Connector::id() const {
    return ACC::id();
}

}
