#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <wx/wx.h>
#include "GameWindow.h"
#include "panels/ConnectionPanel.h"
#include "panels/MainGamePanel.h"

class GameController {
public:
    /**
     * @brief Initializes all panels, displays the connection panel. 
    */
    void init(GameWindow* gameWindow);
    /**
     * @brief Connects to server. 
    */
    void connectToServer();
    /**
     * @brief Sends a start game request after setup phase. 
    */
    void startGame();
    /**
        * @brief Sends a shot request to the server. 
    */
    void callShot();
    /**
     * @brief Sends an emote to the server. 
    */
    void sendEmote();
    /**
     * @brief Prints an error message box in case of an invalid move. 
    */
    void showError(const std::string& title, const std::string& message);
    /**
     * @brief Displays dialog box when game is finished. 
    */
    void showGameOverMessage();
private:
    GameWindow* _gameWindow;
    ConnectionPanel* _connectionPanel;
    MainGamePanel* _mainGamePanel;
};

#endif // GAMECONTROLLER_H