project(shmd-lib)

find_package(ZLIB REQUIRED)

set(PROJECT_SOURCES
        saver.cpp
        loader.cpp
        iracing/irsdk/irsdk_utils.cpp
        iracing/data_iracing.cpp
        iracing/connector_iracing.cpp
        iracing/emulator_iracing.cpp
        application.cpp
        ac/acsdk/shm.cpp
        ac/data_acc.cpp
        ac/connector_acc.cpp
        ac/emulator_acc.cpp
)

add_library(shmd-lib STATIC ${PROJECT_SOURCES})

target_link_libraries(shmd-lib PRIVATE ZLIB::ZLIB)

target_include_directories(shmd-lib PUBLIC
        .
        connectors
        emulators
        iracing
        iracing/irsdk
        ac
        ac/acsdk
)
