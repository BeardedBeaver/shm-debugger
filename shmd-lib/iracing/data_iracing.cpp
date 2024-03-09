#include "data_iracing.h"

namespace iRacing {

std::vector<char> serializeData(const Data& data) {
    size_t size = sizeof(data.header); // overall header
    size_t headerEntryOffset = sizeof(data.header);
    size += sizeof(irsdk_varHeader) * data.header.numVars; // all header entries
    size_t sessionInfoLengthOffset = size;
    size_t sessionInfoLength = data.sessionInfo.size();
    size += sizeof(uint64_t);
    size_t sessionInfoOffset = size;
    size += data.sessionInfo.size();
    size_t rawDataLengthOffset = size;
    size += sizeof(uint64_t);
    size_t rawDataOffset = size;
    size += data.rawDataLength;

    std::vector<char> result;
    result.resize(size);

    memcpy(result.data(),
           reinterpret_cast<const char*>(&data.header),
           sizeof(data.header));

    for (int i = 0; i < data.header.numVars; i++) {
        memcpy(result.data() + headerEntryOffset + sizeof(irsdk_varHeader) * i,
               reinterpret_cast<const char*>(&data.headerEntries[i]),
               sizeof(irsdk_varHeader));
    }

    memcpy(result.data() + sessionInfoLengthOffset,
           reinterpret_cast<const char*>(&sessionInfoLength),
           sizeof(sessionInfoLength));

    memcpy(result.data() + sessionInfoOffset,
           reinterpret_cast<const char*>(data.sessionInfo.c_str()),
           sessionInfoLength);

    memcpy(result.data() + rawDataLengthOffset,
           reinterpret_cast<const char*>(&data.rawDataLength),
           sizeof(data.rawDataLength));

    memcpy(result.data() + rawDataOffset,
           reinterpret_cast<const char*>(data.rawData.get()),
           data.rawDataLength);

    return result;
}

Data deserializeData(const std::vector<char>& bytes) {
    Data result;

    memcpy(&result.header, bytes.data(), sizeof(result.header));
    size_t headerEntryOffset = sizeof(result.header);

    result.headerEntries.resize(result.header.numVars);
    for (int i = 0; i < result.header.numVars; i++) {
        memcpy(&result.headerEntries[i],
               reinterpret_cast<const char*>(bytes.data() + headerEntryOffset + sizeof(irsdk_varHeader) * i),
               sizeof(irsdk_varHeader));
    }

    size_t sessionInfoLengthOffset = headerEntryOffset + sizeof(irsdk_varHeader) * result.header.numVars;
    size_t sessionInfoLength;
    memcpy(&sessionInfoLength, bytes.data() + sessionInfoLengthOffset, sizeof(sessionInfoLength));

    size_t sessionInfoOffset = sessionInfoLengthOffset + sizeof(sessionInfoLength);
    result.sessionInfo.assign(bytes.data() + sessionInfoOffset, sessionInfoLength);

    size_t rawDataLengthOffset = sessionInfoOffset + sessionInfoLength;
    memcpy(&result.rawDataLength, bytes.data() + rawDataLengthOffset, sizeof(result.rawDataLength));

    size_t rawDataOffset = rawDataLengthOffset + sizeof(result.rawDataLength);
    result.rawData = std::make_unique<char[]>(result.rawDataLength);
    memcpy(result.rawData.get(), bytes.data() + rawDataOffset, result.rawDataLength);

    return result;
}

std::array<char, 4> id() {
    return {'i', 'r', 'a', 'c'};
}

}
