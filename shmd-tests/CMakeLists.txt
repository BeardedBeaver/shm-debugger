project(shmd-tests)

find_package(GTest REQUIRED)

enable_testing()

add_executable(shmd-tests
        main.cpp
        data_iracing_test.cpp
        emulator_iracing_test.cpp
        loader_saver_test.cpp
        application_test.cpp
        data_acc_test.cpp)

target_link_libraries(
        shmd-tests
        PRIVATE
        shmd-lib
        GTest::gtest
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
