project(shmd-dumper)

add_executable(shmd-dumper
        main.cpp
        )

target_link_libraries(
        shmd-dumper
        PRIVATE
        shmd-lib
)

find_package(Boost REQUIRED COMPONENTS program_options)
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::program_options)
