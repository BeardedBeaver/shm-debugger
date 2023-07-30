#pragma once

#include <vector>

#include "shm.h"

namespace ACC {

struct Data {
    SPageFileGraphicACC graphics{};
    SPageFilePhysicsACC physics{};
    SPageFileStaticACC statics{};
};

std::vector<char> serializeData(const Data& data);
Data deserializeData(const std::vector<char>& bytes);

}
