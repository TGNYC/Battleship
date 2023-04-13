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
target_compile_features(project_options INTERFACE cxx_std_20)
set(WARNINGS
  -Wall
  -Wextra # reasonable and standard
  -Wextra-semi # Warn about semicolon after in-class function definition.
  -Wshadow # warn the user if a variable declaration shadows one from a parent context
  -Wnon-virtual-dtor # warn the user if a class with virtual functions has a non-virtual destructor. This helps
  # catch hard to track down memory errors
  -Wold-style-cast # warn for c-style casts
  -Wcast-align # warn for potential performance problem casts
  -Wunused # warn on anything being unused
  -Woverloaded-virtual # warn if you overload (not override) a virtual function
  -Wpedantic # warn if non-standard C++ is used
  -Wconversion # warn on type conversions that may lose data
  -Wsign-conversion # warn on sign conversions
  -Wnull-dereference # warn if a null dereference is detected
  -Wdouble-promotion # warn if float is implicit promoted to double
  -Wformat=2 # warn on security issues around functions that format output (ie printf)
  -Wimplicit-fallthrough # warn on statements that fallthrough without an explicit annotation
)
target_compile_options(project_options INTERFACE ${WARNINGS})

add_subdirectory(./src)
