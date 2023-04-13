add_executable(Battleship_Test
    common.cpp)

target_link_libraries(Battleship_Test PRIVATE project_options)
target_link_libraries(Battleship_Test PRIVATE Battleship_Common)

find_package(nlohmann_json REQUIRED)
target_link_libraries(Battleship_Test PUBLIC nlohmann_json::nlohmann_json)

find_package(GTest REQUIRED)
include(GoogleTest)

target_link_libraries(Battleship_Test PRIVATE GTest::gtest GTest::gtest_main)

gtest_discover_tests(Battleship_Test)