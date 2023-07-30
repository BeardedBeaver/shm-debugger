project(shmd-lib)

find_package(ZLIB REQUIRED)

set(PROJECT_SOURCES
        saver.cpp
        loader.cpp
        irsdk/irsdk_utils.cpp
        connector_iracing.cpp
        emulator_iracing.cpp
        data_iracing.cpp
        application.cpp
        connector_acc.cpp
        acsdk/shm.cpp
        data_acc.cpp
        data_acc.h
)

add_library(shmd-lib STATIC ${PROJECT_SOURCES})

target_link_libraries(shmd-lib PRIVATE ZLIB::ZLIB)

target_include_directories(shmd-lib PUBLIC
        .
        connectors
        emulators
        irsdk
        acsdk
)
