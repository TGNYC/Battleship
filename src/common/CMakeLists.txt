add_library(Battleship_Common)

target_sources(Battleship_Common
    PRIVATE
        network/requests/ClientRequest.cpp
        network/requests/JoinGame.cpp
        network/requests/StartGame.cpp
        network/requests/CallShot.cpp
        network/requests/SendEmote.cpp
        network/requests/QuitGame.cpp
        network/requests/PlayAgain.cpp
        uuid.cpp
        game_state/Ship.cpp
    PUBLIC
        network/requests/ClientRequest.h
        network/requests/JoinGame.h
        network/requests/StartGame.h
        network/requests/CallShot.h
        network/requests/SendEmote.h
        network/requests/QuitGame.h
        network/requests/PlayAgain.h
        uuid.h
        serialization/serialization.h
        game_state/Ship.h
        game_state/Coordinate.h)

target_link_libraries(Battleship_Common PRIVATE project_options)

target_include_directories(Battleship_Common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

find_package(nlohmann_json REQUIRED)

#target_link_libraries(Battleship_Common PUBLIC nlohmann_json::nlohmann_json)
