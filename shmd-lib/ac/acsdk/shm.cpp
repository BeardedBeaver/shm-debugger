#include "shm.h"

int shm::initPhysicsAC() {
    TCHAR szName[] = TEXT("Local\\acpmf_physics");
    m_physicsAC.hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, 0, sizeof(SPageFilePhysicsAC), szName);
    if (!m_physicsAC.hMapFile) {
        return 1;
    }
    m_physicsAC.mapFileBuffer = (unsigned char*)MapViewOfFile(m_physicsAC.hMapFile, FILE_MAP_READ, 0, 0, sizeof(SPageFilePhysicsAC));
    if (!m_physicsAC.mapFileBuffer) {
        return 2;
    }
    return 0;
}

int shm::initGraphicsAC() {
    TCHAR szName[] = TEXT("Local\\acpmf_graphics");
    m_graphicsAC.hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, 0, sizeof(SPageFileGraphicAC), szName);
    if (!m_graphicsAC.hMapFile) {
        return 1;
    }
    m_graphicsAC.mapFileBuffer = (unsigned char*)MapViewOfFile(m_graphicsAC.hMapFile, FILE_MAP_READ, 0, 0, sizeof(SPageFileGraphicAC));
    if (!m_graphicsAC.mapFileBuffer) {
        return 2;
    }
    return 0;
}

int shm::initStaticAC() {
    TCHAR szName[] = TEXT("Local\\acpmf_static");
    m_staticAC.hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, 0, sizeof(SPageFileStaticAC), szName);
    //    m_static.hMapFile = OpenFileMapping( FILE_MAP_READ, FALSE, szName);
    if (!m_staticAC.hMapFile) {
        return 1;
    }
    m_staticAC.mapFileBuffer = (unsigned char*)MapViewOfFile(m_staticAC.hMapFile, FILE_MAP_READ, 0, 0, sizeof(SPageFileStaticAC));
    if (!m_staticAC.mapFileBuffer) {
        return 2;
    }
    return 0;
}

int shm::initPhysicsACC() {
    TCHAR szName[] = TEXT("Local\\acpmf_physics");
    m_physicsACC.hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, 0, sizeof(SPageFilePhysicsACC), szName);
    if (!m_physicsACC.hMapFile) {
        return 1;
    }
    m_physicsACC.mapFileBuffer = (unsigned char*)MapViewOfFile(m_physicsACC.hMapFile, FILE_MAP_READ, 0, 0, sizeof(SPageFilePhysicsACC));
    if (!m_physicsACC.mapFileBuffer) {
        return 2;
    }
    return 0;
}

int shm::initGraphicsACC() {
    TCHAR szName[] = TEXT("Local\\acpmf_graphics");
    m_graphicsACC.hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, 0, sizeof(SPageFileGraphicACC), szName);
    if (!m_graphicsACC.hMapFile) {
        return 1;
    }
    m_graphicsACC.mapFileBuffer = (unsigned char*)MapViewOfFile(m_graphicsACC.hMapFile, FILE_MAP_READ, 0, 0, sizeof(SPageFileGraphicACC));
    if (!m_graphicsACC.mapFileBuffer) {
        return 2;
    }
    return 0;
}

int shm::initStaticACC() {
    TCHAR szName[] = TEXT("Local\\acpmf_static");
    m_staticACC.hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, 0, sizeof(SPageFileStaticACC), szName);
    //    m_static.hMapFile = OpenFileMapping( FILE_MAP_READ, FALSE, szName);
    if (!m_staticACC.hMapFile) {
        return 1;
    }
    m_staticACC.mapFileBuffer = (unsigned char*)MapViewOfFile(m_staticACC.hMapFile, FILE_MAP_READ, 0, 0, sizeof(SPageFileStaticACC));
    if (!m_staticACC.mapFileBuffer) {
        return 2;
    }
    return 0;
}

void dismiss(SMElement element) {
    UnmapViewOfFile(element.mapFileBuffer);
    CloseHandle(element.hMapFile);
}
