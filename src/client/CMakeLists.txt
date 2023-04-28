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
  EmoteHandler.h
  uiElements/InputField.cpp
  uiElements/InputField.h
  uiElements/ImagePanel.cpp
  uiElements/ImagePanel.h
  panels/ConnectionPanel.cpp
  panels/ConnectionPanel.h
  panels/SetupPanel.cpp
  panels/SetupPanel.h
  panels/MainGamePanel.cpp
  panels/MainGamePanel.h uiElements/PlacementGrid.cpp uiElements/PlacementGrid.h)

target_link_libraries(Battleship_Client PRIVATE project_options)
target_link_libraries(Battleship_Client PRIVATE Battleship_Common)

find_package(wxWidgets COMPONENTS core base net REQUIRED)
include(${wxWidgets_USE_FILE})

target_link_libraries(Battleship_Client PRIVATE ${wxWidgets_LIBRARIES})
