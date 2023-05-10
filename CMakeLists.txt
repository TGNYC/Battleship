cmake_minimum_required(VERSION 3.16)

option(ENABLE_CLANG_TIDY "Enableing clang-tidy" OFF)
if(ENABLE_CLANG_TIDY)
find_program(CLANG_TIDY clang-tidy REQUIRED)
set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY})
endif()

option(ENABLE_IWYU "Enableing include-what-you-use" OFF)
if(ENABLE_IWYU)
find_program(IWYU iwyu NAMES include-what-you-use REQUIRED)
set(IWYU_WITH_OPTIONS
  ${IWYU}
  -Xiwyu
  --mapping_file=${CMAKE_CURRENT_SOURCE_DIR}/iwyu.imp)
set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE ${IWYU_WITH_OPTIONS})
endif()

project(Battleship VERSION 0.0.1 LANGUAGES CXX)

add_library(Battleship_Common src/common/Logger.cpp src/common/Logger.h src/common/Logger.cpp src/common/Logger.cpp src/common/network/responses/JoinGameSuccess.cpp src/common/network/responses/JoinGameSuccess.h)
target_link_libraries(Battleship_Common PRIVATE project_options)
target_link_libraries(Battleship_Common PUBLIC nlohmann_json::nlohmann_json)

add_executable(Battleship_Server)
target_link_libraries(Battleship_Server PRIVATE project_options)
target_link_libraries(Battleship_Server PRIVATE Battleship_Common)
target_link_libraries(Battleship_Server PRIVATE sockpp)

add_executable(Battleship_Client src/common/network/responses/GameEvent.cpp src/common/network/responses/GameEvent.h src/client/AudioPlayer.cpp src/client/AudioPlayer.h)
target_link_libraries(Battleship_Client PRIVATE project_options)
target_link_libraries(Battleship_Client PRIVATE Battleship_Common)
target_link_libraries(Battleship_Client PRIVATE sockpp)
target_link_libraries(Battleship_Client PRIVATE wx::net wx::core wx::base)

option(ENABLE_TESTING "Enableing Testing" ON)
if(ENABLE_TESTING)
  enable_testing()
  add_executable(Battleship_Test)
  target_link_libraries(Battleship_Test PRIVATE project_options)
  target_link_libraries(Battleship_Test PRIVATE Battleship_Common)
  target_link_libraries(Battleship_Test PRIVATE GTest::gtest GTest::gtest_main)

  include(GoogleTest)
  gtest_discover_tests(Battleship_Test)
  
  add_subdirectory(./test)
endif()

option(ENABLE_DOCS "Enableing Documentation" OFF)
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

include(FetchContent)

FetchContent_Declare(sockpp
  GIT_REPOSITORY https://github.com/fpagliughi/sockpp.git
  GIT_TAG        v0.8.1
  # SYSTEM
)
FetchContent_Declare(googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.13.0
  # SYSTEM
)
FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG        v3.11.2
  # SYSTEM
)
FetchContent_Declare(wxWidgets
  GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets.git
  GIT_TAG        v3.2.2.1
  # SYSTEM
)

FetchContent_MakeAvailable(sockpp googletest json wxWidgets)

# Set the includes for the expern libarays as systme to disabel the warnings
# https://stackoverflow.com/questions/56707123/how-to-suppress-clang-warnings-in-third-party-library-header-file-in-cmakelists
set_target_properties(gtest PROPERTIES INTERFACE_SYSTEM_INCLUDE_DIRECTORIES $<TARGET_PROPERTY:gtest,INTERFACE_INCLUDE_DIRECTORIES>)
set_target_properties(gtest_main PROPERTIES INTERFACE_SYSTEM_INCLUDE_DIRECTORIES $<TARGET_PROPERTY:gtest_main,INTERFACE_INCLUDE_DIRECTORIES>)

set_target_properties(wxnet PROPERTIES INTERFACE_SYSTEM_INCLUDE_DIRECTORIES $<TARGET_PROPERTY:wxnet,INTERFACE_INCLUDE_DIRECTORIES>)
set_target_properties(wxcore PROPERTIES INTERFACE_SYSTEM_INCLUDE_DIRECTORIES $<TARGET_PROPERTY:wxcore,INTERFACE_INCLUDE_DIRECTORIES>)
set_target_properties(wxbase PROPERTIES INTERFACE_SYSTEM_INCLUDE_DIRECTORIES $<TARGET_PROPERTY:wxbase,INTERFACE_INCLUDE_DIRECTORIES>)

set_target_properties(nlohmann_json PROPERTIES INTERFACE_SYSTEM_INCLUDE_DIRECTORIES $<TARGET_PROPERTY:nlohmann_json,INTERFACE_INCLUDE_DIRECTORIES>)

set_target_properties(sockpp PROPERTIES INTERFACE_SYSTEM_INCLUDE_DIRECTORIES $<TARGET_PROPERTY:sockpp,INTERFACE_INCLUDE_DIRECTORIES>)

add_subdirectory(./src)
