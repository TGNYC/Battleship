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
#include "exceptions/BattleshipException.h"

// Macro to include function name in log message
#define LOG(message) Logger::log(message, __func__)

/*!
 * Basic logging class. Use LOG(msg) macro anywhere in the project to log whatever you need.
 */
class Logger {  //TODO idk if this class is actually thread safe. should technically at least not crash stuff

public:
  /*!
   * outputs a message to std::cout and to the logfile
   * @param message text to be logged
   * @param type optional log type (info, warning, error). currently unused
   */
  static void log(const std::string& message, const std::string &function = "-");

  /*!
   * overloading of log to output BattleshipExceptions directly
   * @param exception
   */
  static void log(const BattleshipException &exception);

  static void setPrefix(const std::string &s);

private:
  /*!
   * Helper function for logging
   * @return returns a formatted string timestamp
   */
  static std::string getCurrentDateTime();

  static std::string prefix;  ///< prefix for logging messages. intended to be "client" or "server"
  static const char* const logFile; ///< file path for the log file
  static const char* const tab;   ///< defines a tabulator for formatting
};

#endif // BATTLESHIP_LOGGER_H
