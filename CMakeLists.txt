cmake_minimum_required(VERSION 3.20)

project(Battleship VERSION 0.0.1 LANGUAGES CXX)

add_subdirectory(./src)

option(ENABLE_TESTING "Enabeling Testing" ON)
if(ENABLE_TESTING)
  enable_testing()
  add_subdirectory(./test)
endif()

option(ENABLE_DOCS "Enabeling Documentation" ON)
if(ENABLE_DOCS)
  find_package(Doxygen REQUIRED)
  doxygen_add_docs(Battleship_Docs)
endif()
