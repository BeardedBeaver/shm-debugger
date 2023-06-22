#include "iracing_data.h"

namespace iRacing {
    std::vector<char> serializeData(const Data &data) {
        size_t size = sizeof(data.header) + sizeof(data.headerEntry);
        size_t headerEntryOffset = sizeof(data.header);
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
        memcpy(result.data(), reinterpret_cast<const char*>(&data.header), sizeof(data.header));
        memcpy(result.data() + headerEntryOffset, reinterpret_cast<const char*>(&data.headerEntry), sizeof(data.headerEntry));
        memcpy(result.data() + sessionInfoLengthOffset, reinterpret_cast<const char*>(&sessionInfoLength), sizeof(sessionInfoLength));
        memcpy(result.data() + sessionInfoOffset, reinterpret_cast<const char*>(data.sessionInfo.c_str()), sessionInfoLength);
        memcpy(result.data() + rawDataLengthOffset, reinterpret_cast<const char*>(&data.rawDataLength), sizeof(data.rawDataLength));
        memcpy(result.data() + rawDataOffset, reinterpret_cast<const char*>(data.rawData.get()), data.rawDataLength);

        return result;
    }

    Data deserializeData(const std::vector<char>& bytes) {
        Data result;

        memcpy(&result.header, bytes.data(), sizeof(result.header));
        size_t headerEntryOffset = sizeof(result.header);

        memcpy(&result.headerEntry, bytes.data() + headerEntryOffset, sizeof(result.headerEntry));

        size_t sessionInfoLengthOffset = headerEntryOffset + sizeof(result.headerEntry);
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
}
