add_executable(Battleship_Test sample.cpp)

target_link_libraries(Battleship_Test PRIVATE project_options)

find_package(GTest REQUIRED)
include(GoogleTest)

target_link_libraries(Battleship_Test PRIVATE GTest::gtest GTest::gtest_main)

gtest_discover_tests(Battleship_Test)