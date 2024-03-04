#include "emulator_iracing.h"

#include <cassert>
#include <stdexcept>

#include "data_iracing.h"
#include "irsdk_defines.h"

namespace iRacing {

void Emulator::initialize() {
    assert(m_fileMappingHandle == nullptr);
    assert(m_memMapFile == nullptr);
    assert(m_sharedMem == nullptr);
    assert(m_dataValidEvent == nullptr);
    uint64_t bufSize = 1024 * 1024 * 1024; // probably way too much
    m_fileMappingHandle = CreateFileMapping(INVALID_HANDLE_VALUE,
                                            nullptr,
                                            PAGE_READWRITE,
                                            0,
                                            bufSize,
                                            IRSDK_MEMMAPFILENAME);
    if (m_fileMappingHandle == nullptr) {
        throw std::runtime_error("Failed to create file mapping");
    }

    m_memMapFile = OpenFileMapping(FILE_MAP_WRITE,
                                   FALSE,
                                   IRSDK_MEMMAPFILENAME);
    if (m_memMapFile == nullptr) {
        CloseHandle(m_fileMappingHandle);
        throw std::runtime_error("Failed to open file mapping");
    }

    m_sharedMem = (char*)MapViewOfFile(m_fileMappingHandle,
                                       FILE_MAP_WRITE,
                                       0,
                                       0,
                                       bufSize);
    if (m_sharedMem == nullptr) {
        CloseHandle(m_fileMappingHandle);
        CloseHandle(m_memMapFile);
        throw std::runtime_error("Failed to map view");
    }

    m_dataValidEvent = CreateEvent(nullptr,
                                   FALSE,
                                   FALSE,
                                   IRSDK_DATAVALIDEVENTNAME);
    if (m_dataValidEvent == nullptr) {
        CloseHandle(m_fileMappingHandle);
        CloseHandle(m_memMapFile);
        throw std::runtime_error("Failed to create event mapping");
    }

    assert(m_fileMappingHandle != nullptr);
    assert(m_memMapFile != nullptr);
    assert(m_sharedMem != nullptr);
    assert(m_sharedMem != nullptr);
}

void Emulator::update(const std::vector<char>& bytes) {
    auto data = iRacing::deserializeData(bytes);
    memcpy((void*)m_sharedMem, &data.header, sizeof(irsdk_header));
    int latest = 0;
    for (int i = 1; i < data.header.numBuf; i++)
        if (data.header.varBuf[latest].tickCount < data.header.varBuf[i].tickCount)
            latest = i;

    memcpy(m_sharedMem + data.header.varBuf[latest].bufOffset, data.rawData.get(), data.header.bufLen);
    memcpy(m_sharedMem + data.header.varHeaderOffset, &data.headerEntry, sizeof(data.headerEntry));
    if (!data.sessionInfo.empty()) {
        memcpy(m_sharedMem + data.header.sessionInfoOffset, data.sessionInfo.c_str(), data.sessionInfo.size());
    }
}

Emulator::~Emulator() {
    Emulator::stop();
}

void Emulator::stop() {
    if (m_sharedMem == nullptr) {
        return;
    }
    UnmapViewOfFile(m_sharedMem);
    CloseHandle(m_fileMappingHandle);
    CloseHandle(m_memMapFile);
    CloseHandle(m_dataValidEvent);
    m_sharedMem = nullptr;
    m_fileMappingHandle = nullptr;
    m_memMapFile = nullptr;
    m_dataValidEvent = nullptr;
}

}
