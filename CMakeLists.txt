cmake_minimum_required(VERSION 3.10)

project(Battleship VERSION 0.0.1 LANGUAGES CXX)

add_subdirectory(./src)

option(ENABLE_TESTING "Enabeling Testing" OFF)
if(ENABLE_TESTING)
  enable_testing()
  add_subdirectory(./test)
endif()