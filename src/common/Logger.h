//
// Created by nico on 04.05.23.
//

#ifndef BATTLESHIP_LOGGER_H
#define BATTLESHIP_LOGGER_H

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <ctime>
#include "sstream"

/*!
 * Basic logging class. Only static usage
 */
class Logger {

public:

  enum class Type {
    Info,
    Warning,
    Error
  };

  /*!
   * outputs a message to the logfile
   * @param message text to be logged
   * @param type optional log type (info, warning, error). currently unused
   */
  static void log(const char* message, Type type = Type::Info);

private:
  /*!
   * Helper function for logging
   * @return returns a formatted string timestamp
   */
  static std::string getCurrentDateTime();
  static const char* logFile;
};

#endif // BATTLESHIP_LOGGER_H
