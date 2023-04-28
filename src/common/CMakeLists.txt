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
        game_state/player.cpp
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
        game_state/player.h
        game_state/Coordinate.h
        game_state/game_state.h)

target_include_directories(Battleship_Common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
