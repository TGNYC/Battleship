add_executable(Battleship_Client
  main.cpp
  Battleship.cpp
  Battleship.h
  GameController.cpp
  GameController.h
  GameWindow.cpp
  GameWindow.h
  ClientNetworkManager.cpp
  ClientNetworkManager.h
  SetupManager.cpp
  SetupManager.h
  EmoteHandler.cpp
  EmoteHandler.h)

target_link_libraries(Battleship_Client PRIVATE project_options)
target_link_libraries(Battleship_Client PRIVATE Battleship_Common)

find_package(wxWidgets COMPONENTS core base net REQUIRED)
include(${wxWidgets_USE_FILE})

target_link_libraries(Battleship_Client PRIVATE ${wxWidgets_LIBRARIES})
