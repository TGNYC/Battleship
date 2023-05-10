#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <wx/wx.h>
#include "GameWindow.h"
#include "panels/ConnectionPanel.h"
#include "panels/MainGamePanel.h"
#include "panels/SetupPanel.h"
#include "SetupManager.h"

class GameController {
public:
    /**
     * @brief Initializes all panels, displays the connection panel. 
    */
    static void init(GameWindow* gameWindow);
    /**
     * @brief enter setup phase
     */
    static void enterSetupPhase();
    /**
     * @brief Connects to server. 
    */
    static void connectToServer();
    /**
     * @brief Sends a start game request after setup phase. 
    */
    static void startGame();
    /**
        * @brief Sends a shot request to the server. 
    */
    static void callShot();
    /**
     * @brief Sends an emote to the server. 
    */
    static void sendEmote();
    /**
     * @brief Prints an error message box in case of an invalid move. 
    */
    static void showError(const std::string& title, const std::string& message);
    /**
     * @brief Displays dialog box when game is finished. 
    */
    static void showGameOverMessage();

    static SetupPanel* getSetupPanel() {
      return _setupPanel;
    }

    static void playerReady();

private:
    static GameWindow* _gameWindow;
    static ConnectionPanel* _connectionPanel;
    static SetupPanel* _setupPanel;
    static MainGamePanel* _mainGamePanel;

    static SetupManager *_setupManager;

    static game_state* _gameState;
};

#endif // GAMECONTROLLER_H