#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "EmoteHandler.h"
#include "GameWindow.h"
#include "SetupManager.h"
#include "game_state/Player.h"
#include "network/responses/EmoteEvent.h"
#include "network/responses/StartGameSuccess.h"
#include "network/responses/GameEvent.h"
#include "network/responses/QuitGameEvent.h"
#include "panels/ConnectionPanel.h"
#include "panels/MainGamePanel.h"
#include "panels/SetupPanel.h"
#include <wx/wx.h>

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
    static void startGame(const StartGameSuccess &response);
    /**
     * @brief Handes shot. 
    */
    static void handleGameEvent(const GameEvent &event);
    /**
        * @brief Sends a shot request to the server. 
    */
    static void callShot(Coordinate position);
    /**
     * @brief Sends an emote to the server. 
    */
    static void sendEmote(EmoteType emote);
    /**
     * @brief Displays an emote to the screen
     */
     static void showEmote(EmoteEvent emoteEvent);
    /**
     * @brief Prints an error message box in case of an invalid move. 
    */
    static void showError(const std::string& title, const std::string& message, bool popup);
    /**
     * @brief Displays dialog box when game is finished. 
    */
    static void showGameOverMessage();

    static SetupPanel* getSetupPanel() {
      return _setupPanel;
    }

    static wxEvtHandler* getMainThreadEventHandler();

    static void playerReady();

    static void quitGame();

private:
    static GameWindow* _gameWindow;
    static ConnectionPanel* _connectionPanel;
    static SetupPanel* _setupPanel;
    static MainGamePanel* _mainGamePanel;

    static SetupManager *_setupManager;

    static GameState * _gameState;
    static Player *_me;
};

#endif // GAMECONTROLLER_H