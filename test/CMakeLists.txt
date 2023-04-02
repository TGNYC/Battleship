add_executable(Battleship_Test sample.cpp)

find_package(GTest REQUIRED)
include(GoogleTest)

target_link_libraries(Battleship_Test GTest::gtest GTest::gtest_main)

gtest_discover_tests(Battleship_Test)