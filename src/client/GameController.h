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
#include <chrono>

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
    static void gameOver(uuid winnerId);

    /*!
     * shows popup saying that the other player left.
     * closing the popup brings you back to the connection panel.
     * @param leaverId id of the player who quit
     */
    static void handleQuitGameEvent(uuid quitterId);

    static SetupPanel* getSetupPanel() {
      return _setupPanel;
    }

    static wxEvtHandler* getMainThreadEventHandler();

    /**
    * @brief function that is called when ready button in SetupPanel is clicked.
     * Will send request to server to start game and creates GameState used on client side.
    */
    static void playerReady();

    /*!
     * sends a QuitGame request to the server
     * is being called upon closing the main window
     */
    static void quitGame();

private:
    static GameWindow* _gameWindow;
    static ConnectionPanel* _connectionPanel;
    static SetupPanel* _setupPanel;
    static MainGamePanel* _mainGamePanel;

    static SetupManager *_setupManager;

    static GameState * _gameState;
    static Player *_me;
    static std::chrono::system_clock::time_point _lastClick;
};

#endif // GAMECONTROLLER_H