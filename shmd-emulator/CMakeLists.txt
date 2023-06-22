project(shmd-emulator)

add_executable(shmd-emulator
        main.cpp
        )

target_link_libraries(
        shmd-emulator
        PRIVATE
        shmd-lib
)

find_package(Boost REQUIRED COMPONENTS program_options)
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::program_options)
