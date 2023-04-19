#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

class GameController {
public:
    /**
     * @brief Initializes all panels, displays the connection panel. 
    */
    auto init() -> bool;
    /**
     * @brief Connects to server. 
    */
    auto connectToServer() -> bool;
    /**
     * @brief Sends a start game request after setup phase. 
    */
    auto startGame() -> bool;
    /**
        * @brief Sends a shot request to the server. 
    */
    auto callShot() -> bool;
    /**
     * @brief Sends an emote to the server. 
    */
    auto sendEmote() -> bool;
    /**
     * @brief Prints an error message box in case of an invalid move. 
    */
    auto showError() -> bool;
    /**
     * @brief Displays dialog box when game is finished. 
    */
    auto showGameOverMessage() -> bool;
};

#endif // GAMECONTROLLER_H