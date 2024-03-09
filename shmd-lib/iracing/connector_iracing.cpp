#include "connector_iracing.h"

#include "data_iracing.h"

#include <exception>
#include <iostream>

namespace iRacing {

bool Connector::connect(int timeoutMs) {
    bool result = irsdk_startup();
    if (result) {
        const irsdk_header* header = irsdk_getHeader();
        if (header) {
            if (header->bufLen != rawDataLength) {
                rawDataLength = header->bufLen;
                rawData = std::unique_ptr<char[]>(new char[rawDataLength]);
            }
            if (irsdk_waitForDataReady(timeoutMs, rawData.get()))
                return true;
            irsdk_shutdown();
            return false;
        }
        irsdk_shutdown();
        return false;
    }
    return false;
}

void Connector::disconnect() {
    irsdk_shutdown();
}

std::vector<char> Connector::update(int timeoutMs) {
    if (irsdk_waitForDataReady(timeoutMs, rawData.get())) {
        const irsdk_header* header = irsdk_getHeader();
        if (header && rawData) {
            if (header->bufLen != rawDataLength) {
                rawDataLength = header->bufLen;
                rawData = std::unique_ptr<char[]>(new char[rawDataLength]);
            }

            Data data{};
            data.rawDataLength = rawDataLength;
            data.rawData = std::unique_ptr<char[]>(new char[rawDataLength]);
            memcpy(data.rawData.get(), rawData.get(), rawDataLength);

            if (header->sessionInfoUpdate != sessionInfoUpdate) {
                sessionInfoUpdate = header->sessionInfoUpdate;
                data.sessionInfo = std::string(irsdk_getSessionInfoStr());
            }

            data.headerEntries.reserve(header->numVars);
            for (int i = 0; i < header->numVars; i++) {
                data.headerEntries.push_back(*irsdk_getVarHeaderEntry(i));
            }
            data.header = *header;

            auto result = serializeData(data);
            return result;
        }
    }
    return {};
}
std::array<char, 4> Connector::id() const {
    return iRacing::id();
}

}
