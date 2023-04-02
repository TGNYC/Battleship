cmake_minimum_required(VERSION 3.20)

project(Battleship VERSION 0.0.1 LANGUAGES CXX)

add_library(project_options INTERFACE)
target_compile_options(project_options INTERFACE -Wall -Wextra -Wpedantic)
target_compile_features(project_options INTERFACE cxx_std_20)

add_subdirectory(./src)

option(ENABLE_TESTING "Enabeling Testing" ON)
if(ENABLE_TESTING)
  enable_testing()
  add_subdirectory(./test)
endif()

option(ENABLE_DOCS "Enabeling Documentation" ON)
if(ENABLE_DOCS)
  find_package(Doxygen REQUIRED)
  doxygen_add_docs(Battleship_Docs ALL)
endif()
