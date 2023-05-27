#ifndef BATTLESHIP_RESPONSELISTENERTHREAD_H
#define BATTLESHIP_RESPONSELISTENERTHREAD_H

#include <sockpp/tcp_connector.h>
#include <wx/wx.h>

/*!
 * Thread that is permanently listening for messages from the server
 */
class ResponseListenerThread : public wxThread {

public:
  ResponseListenerThread(sockpp::tcp_connector *connection);

protected:
  virtual ExitCode Entry();

private:
  void outputError(std::string title, std::string message);

  sockpp::tcp_connector *_connection;
};

#endif // BATTLESHIP_RESPONSELISTENERTHREAD_H