#include "ResponseListenerThread.h"

#include "ClientNetworkManager.h"
#include "GameController.h"
#include "network/responses/ErrorResponse.h"
#include <sstream>

ResponseListenerThread::ResponseListenerThread(sockpp::tcp_connector *connection) {
  this->_connection = connection;
}

ResponseListenerThread::~ResponseListenerThread() {
  this->_connection->shutdown();
}

wxThread::ExitCode ResponseListenerThread::Entry() {
  try {
    char    buffer[512]; // 512 bytes
    ssize_t count = 0;

    while ((count = this->_connection->read(buffer, sizeof(buffer))) > 0) {
      std::cout << "Client listening...\n";
      try {
        int pos = 0;

        // extract length of message in bytes (which is sent at the start of the message, and is separated by a ":")
        std::stringstream messageLengthStream;
        while (buffer[pos] != ':' && pos < count) {
          messageLengthStream << buffer[pos];
          pos++;
        }
        ssize_t messageLength = std::stoi(messageLengthStream.str());

        // initialize a stream for the message
        std::stringstream messageStream;

        // copy everything following the message length declaration into a stringstream
        messageStream.write(&buffer[pos + 1], count - (pos + 1));
        ssize_t bytesReadSoFar = count - (pos + 1);

        // read remaining packages until full message length is reached
        while (bytesReadSoFar < messageLength && count != 0) {
          count = this->_connection->read(buffer, sizeof(buffer));
          messageStream.write(buffer, count);
          bytesReadSoFar += count;
        }

        // process message (if we've received entire message)
        if (bytesReadSoFar == messageLength) {
          std::cout << "Received entire message...\n";
          std::string message = messageStream.str();
          std::cout << "1\n";
          std::cout << "Message: " << message << std::endl;
          std::unique_ptr<ServerResponse> response = ClientNetworkManager::parseResponse(message);

          std::cout << "Response type: " << static_cast<int>(response->responseType) << std::endl;

          switch (response->responseType) {

          case ResponseType::GameEvent:
            GameController::getMainThreadEventHandler()->CallAfter([&response] {
              GameController::handleGameEvent(static_cast<const GameEvent&>(*response));
            });
            break;
          case ResponseType::EmoteEvent:
            GameController::getMainThreadEventHandler()->CallAfter([&response]{
              GameController::showEmote(static_cast<const EmoteEvent&>(*response));
            });
            break;
          case ResponseType::JoinGameSuccess:
            std::cout << "Client received a JoinGameSuccess...\n";
            GameController::getMainThreadEventHandler()->CallAfter([] {
              GameController::enterSetupPhase();
            });
            break;
          case ResponseType::ErrorResponse:
            GameController::getMainThreadEventHandler()->CallAfter([&response] {
              GameController::showError("Server Error", static_cast<const ErrorResponse &>(*response).exception.what());
            });
            break;
          case ResponseType::StartGameSuccess:
            GameController::getMainThreadEventHandler()->CallAfter([] {
              GameController::startGame();
            });
            break;
          }
        } else {
          this->outputError("Network error", "Could not read entire message. TCP stream ended early. Difference is " +
                                                 std::to_string(messageLength - bytesReadSoFar) + " bytes");
        }

      } catch (std::exception &e) {
        // Make sure the connection isn't terminated only because of a read error
        this->outputError("Network error", "Error while reading message: " + (std::string)e.what());
      }
    }

    if (count <= 0) {
      this->outputError("Network error", "Read error [" + std::to_string(this->_connection->last_error()) +
                                             "]: " + this->_connection->last_error_str());
    }

  } catch (const std::exception &e) {
    this->outputError("Network error", "Error in listener thread: " + (std::string)e.what());
  }

  this->_connection->shutdown();

  return (wxThread::ExitCode)0; // everything okay
}

void ResponseListenerThread::outputError(std::string title, std::string message) {
  // TODO GameController getMainThreadEventHandler
  //   GameController::getMainThreadEventHandler()->CallAfter([title, message] {
  //     GameController::showError(title, message);
  //   });
}
