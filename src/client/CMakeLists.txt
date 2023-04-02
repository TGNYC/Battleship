add_executable(Battleship_Client
  main.cpp
  Battleship.cpp
  Battleship.h
  GameWindow.cpp
  GameWindow.h)

find_package(wxWidgets COMPONENTS core base net REQUIRED)
include(${wxWidgets_USE_FILE})
target_link_libraries(Battleship_Client ${wxWidgets_LIBRARIES})