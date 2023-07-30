#pragma once

#include "SharedFileOutAC.h"
#include "SharedFileOutACC.h"

#include <windows.h>
#include <iostream>

template <typename T, unsigned S>
inline unsigned arraysize(const T (&v)[S]) {
    return S;
}

struct SMElement {
    HANDLE hMapFile = nullptr;
    unsigned char* mapFileBuffer;
};

class shm {
public:
    // AC
    SMElement m_graphicsAC;
    SMElement m_physicsAC;
    SMElement m_staticAC;

    // ACC
    SMElement m_graphicsACC;
    SMElement m_physicsACC;
    SMElement m_staticACC;

    int initPhysicsAC();
    int initGraphicsAC();
    int initStaticAC();

    int initGraphicsACC();
    int initPhysicsACC();
    int initStaticACC();
};

void dismiss(SMElement element);
