project(shmd-tests)

find_package(GTest REQUIRED)

add_executable(shmd-tests
        main.cpp
        iracing_data_test.cpp
        iracing_emulator_test.cpp
        loader_saver_test.cpp
        application_test.cpp)

target_link_libraries(
        shmd-tests
        PRIVATE
        shmd-lib
        GTest::gtest
        GTest::gtest_main
)
