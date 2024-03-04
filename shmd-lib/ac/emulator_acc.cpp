#include <cassert>
#include "emulator_acc.h"
#include "data_acc.h"

namespace ACC {

Emulator::~Emulator() {
    Emulator::stop();
}

void Emulator::initialize() {
    uint64_t bufSize = 5000;
    m_graphicsACC.hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE,
                                               nullptr,
                                               PAGE_READWRITE,
                                               0,
                                               bufSize,
                                               "Local\\acpmf_graphics");

    m_physicsACC.hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE,
                                              nullptr,
                                              PAGE_READWRITE,
                                              0,
                                              bufSize,
                                              "Local\\acpmf_physics");

    m_staticACC.hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE,
                                             nullptr,
                                             PAGE_READWRITE,
                                             0,
                                             bufSize,
                                             "Local\\acpmf_static");

    if (m_graphicsACC.hMapFile == nullptr ||
        m_physicsACC.hMapFile == nullptr ||
        m_staticACC.hMapFile == nullptr) {
        throw std::runtime_error("Failed to create file mapping");
    }

    m_graphicsACC.mapFileBuffer = (unsigned char*)MapViewOfFile(m_graphicsACC.hMapFile,
                                                                FILE_MAP_WRITE,
                                                                0,
                                                                0,
                                                                bufSize);

    m_physicsACC.mapFileBuffer = (unsigned char*)MapViewOfFile(m_physicsACC.hMapFile,
                                                               FILE_MAP_WRITE,
                                                               0,
                                                               0,
                                                               bufSize);
    m_staticACC.mapFileBuffer = (unsigned char*)MapViewOfFile(m_staticACC.hMapFile,
                                                              FILE_MAP_WRITE,
                                                              0,
                                                              0,
                                                              bufSize);

    if (m_graphicsACC.mapFileBuffer == nullptr ||
        m_physicsACC.mapFileBuffer == nullptr ||
        m_staticACC.mapFileBuffer == nullptr) {
        CloseHandle(m_graphicsACC.mapFileBuffer);
        CloseHandle(m_physicsACC.mapFileBuffer);
        CloseHandle(m_staticACC.mapFileBuffer);
        throw std::runtime_error("Failed to map view");
    }
}

void Emulator::update(const std::vector<char>& bytes) {
    auto data = deserializeData(bytes);

    assert(m_graphicsACC.mapFileBuffer != nullptr);
    assert(m_physicsACC.mapFileBuffer != nullptr);
    assert(m_staticACC.mapFileBuffer != nullptr);

    memcpy(m_graphicsACC.mapFileBuffer, &data.graphics, sizeof(SPageFileGraphicACC));
    memcpy(m_physicsACC.mapFileBuffer, &data.physics, sizeof(SPageFilePhysicsACC));
    memcpy(m_staticACC.mapFileBuffer, &data.statics, sizeof(SPageFileStaticACC));
}

void Emulator::stop() {
    if (m_graphicsACC.mapFileBuffer == nullptr) {
        return;
    }
    ((SPageFileGraphicACC*)m_graphicsACC.mapFileBuffer)->status = AC_OFF;
    CloseHandle(m_graphicsACC.mapFileBuffer);
    CloseHandle(m_physicsACC.mapFileBuffer);
    CloseHandle(m_staticACC.mapFileBuffer);
}

}
