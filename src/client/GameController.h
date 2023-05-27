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
     * Is also used to reset everything on GameOver or QuitGameEvent
    */
    static void init(GameWindow* gameWindow);

    /**
     * @brief Connects to server. Is called when connect button on ConnectionPanel is clicked.
    */
    static void connectToServer();

    /**
     * @brief enter setup phase. Is called when server responds with JoinGameSuccess response. Will show setup panel.
     */
    static void enterSetupPhase();

    /**
     * @brief Function that is called when server responds with StartGameSuccess. Will show main game panel.
    */
    static void startGame(const StartGameSuccess &response);

    /**
     * @brief Handles an incoming GameEvent. GameEvents are sent by the server when one of the players has placed a shot. 
     * The function will update the game state and display the new game state in the main game panel.
    */
    static void handleGameEvent(const GameEvent &event);

    /**
    * @brief Sends a shot request to the server.
    */
    static void callShot(Coordinate position);

    /**
     * @brief Sends an emote to the server. 
     * @param emote The emote to be sent. EmoteType is an enum with 6 possible emotes.
    */
    static void sendEmote(EmoteType emote);

    /**
     * @brief Displays an emote to the screen and plays the corresponding sound.
     */
     static void showEmote(const EmoteEvent &emoteEvent);

    /**
     * @brief Prints an error message to the console. If popup is true, it will also display a popup with the error message.
     * @param title The title of the popup.
     * @param message The message to be displayed.
     * @param popup Whether or not to display a popup window.
    */
    static void showError(const std::string& title, const std::string& message, bool popup);

    /**
     * @brief Displays dialog box when game is finished and resets the game so both players are back at the connection panel.
    */
    static void gameOver(uuid winnerId);

    /**
     * @brief Shows popup saying that the other player left, closing the popup brings you back to the connection panel.
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
     * @brief Sends a QuitGame request to the server, is called upon closing the main window.
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