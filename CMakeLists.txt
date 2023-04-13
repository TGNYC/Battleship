cmake_minimum_required(VERSION 3.20)

option(ENABLE_CLANG_TIDY "Enabeling clang-tidy" OFF)
if(ENABLE_CLANG_TIDY)
find_program(CLANG_TIDY clang-tidy REQUIRED)
set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY})
endif()

option(ENABLE_IWYU "Enabeling include-what-you-use" OFF)
if(ENABLE_IWYU)
find_program(IWYU iwyu NAMES include-what-you-use REQUIRED)
set(IWYU_WITH_OPTIONS
  ${IWYU}
  -Xiwyu
  --mapping_file=${CMAKE_CURRENT_SOURCE_DIR}/iwyu.imp)
set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE ${IWYU_WITH_OPTIONS})
endif()

project(Battleship VERSION 0.0.1 LANGUAGES CXX)

option(ENABLE_TESTING "Enabeling Testing" ON)
if(ENABLE_TESTING)
  enable_testing()
  add_subdirectory(./test)
endif()

option(ENABLE_DOCS "Enabeling Documentation" OFF)
if(ENABLE_DOCS)
  find_package(Doxygen REQUIRED)
  doxygen_add_docs(Battleship_Docs ALL)
endif()

add_library(project_options INTERFACE)
target_compile_options(project_options INTERFACE -Wall -Wextra -Wpedantic)
target_compile_features(project_options INTERFACE cxx_std_20)

add_subdirectory(./src)
