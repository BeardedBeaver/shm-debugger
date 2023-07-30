#include "acc_data.h"

std::vector<char> ACC::serializeData(const ACC::Data& data) {
    // to catch potential changes
    static_assert(sizeof(SPageFileGraphicACC) == 1588);
    static_assert(sizeof(SPageFilePhysicsACC) == 800);
    static_assert(sizeof(SPageFileStaticACC) == 756);

    const size_t totalGraphicsSize = 1700;
    const size_t totalPhysicsSize = 1000;
    const size_t totalStaticSize = 1000;

    size_t size = 0;
    size += totalGraphicsSize;
    size += totalPhysicsSize;
    size += totalStaticSize;

    std::vector<char> result;
    result.resize(size);

    // Copy graphics data and add padding
    memcpy(result.data(), &data.graphics, sizeof(SPageFileGraphicACC));
    std::memset(result.data() + sizeof(SPageFileGraphicACC), 0, totalGraphicsSize - sizeof(SPageFileGraphicACC));

    // Copy physics data and add padding
    memcpy(result.data() + totalGraphicsSize, &data.physics, sizeof(SPageFilePhysicsACC));
    std::memset(result.data() + totalGraphicsSize + sizeof(SPageFilePhysicsACC), 0, totalPhysicsSize - sizeof(SPageFilePhysicsACC));

    // Copy statics data and add padding
    memcpy(result.data() + totalGraphicsSize + totalPhysicsSize, &data.statics, sizeof(SPageFileStaticACC));
    std::memset(result.data() + totalGraphicsSize + totalPhysicsSize + sizeof(SPageFileStaticACC), 0, totalStaticSize - sizeof(SPageFileStaticACC));

    return result;
}

ACC::Data ACC::deserializeData(const std::vector<char>& bytes) {
    return {};
}
