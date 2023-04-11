add_library(Battleship_Common
    ClientRequest.cpp
    ClientRequest.h
    JoinGame.cpp
    JoinGame.h
    StartGame.cpp
    StartGame.h
    CallShot.cpp
    CallShot.h
    SendEmote.cpp
    SendEmote.h
    QuitGame.cpp
    QuitGame.h
    PlayAgain.cpp
    PlayAgain.h)

find_package(nlohmann_json REQUIRED)

target_link_libraries(Battleship_Common PRIVATE nlohmann_json::nlohmann_json)