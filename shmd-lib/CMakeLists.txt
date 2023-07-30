project(shmd-lib)

find_package(ZLIB REQUIRED)

set(PROJECT_SOURCES
        saver.cpp
        loader.cpp
        irsdk/irsdk_utils.cpp
        iracing_connector.cpp
        iracing_emulator.cpp
        iracing_data.cpp
        application.cpp
        acc_connector.cpp
        acsdk/shm.cpp
        acc_data.cpp
        acc_data.h
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
