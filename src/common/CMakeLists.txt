add_library(Battleship_Common)

target_sources(Battleship_Common
    PRIVATE
        ClientRequest.cpp
        JoinGame.cpp
        StartGame.cpp
        CallShot.cpp
        SendEmote.cpp
        QuitGame.cpp
        PlayAgain.cpp
        uuid.cpp
        Ship.cpp
    PUBLIC
        ClientRequest.h
        JoinGame.h
        StartGame.h
        CallShot.h
        SendEmote.h
        QuitGame.h
        PlayAgain.h
        uuid.h
        serialization.h
        Ship.h
        Coordinate.h)

target_link_libraries(Battleship_Common PRIVATE project_options)

target_include_directories(Battleship_Common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

find_package(nlohmann_json REQUIRED)

target_link_libraries(Battleship_Common PUBLIC nlohmann_json::nlohmann_json)
