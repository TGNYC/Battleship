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
 * Custom basic logging class. Use the macro LOG(msg) anywhere in the project to log whatever you need.
 */
class Logger {  //TODO idk if this class is actually thread safe. should technically at least not crash stuff

public:
  /*!
   * outputs a message to std::cout and to the logfile.
   * Use the LOG(msg) macro instead of this function whenever possible
   * @param message text to be logged
   * @param function name of the function where this log was called. automatically filled in by the macro
   */
  static void log(const std::string& message, const std::string &function = "-");

  /*!
   * overloading of Logger::log to output BattleshipExceptions directly
   * @param exception
   */
  static void log(const BattleshipException &exception);

  /*!
   * changes the prefix used at the very beginning of a log message.
   * use this if you run multiple instances (servers and clients) on the same machine
   * to identify more easily where the message came from
   * @param s
   */
  static void setPrefix(const std::string &s);

private:
  /*!
   * Helper function to include timestamps with log messages
   * @return returns a formatted string timestamp "dd-mm-yyyy hh-mm-ss"
   */
  static std::string getCurrentDateTime();

  static std::string       _prefix;  ///< prefix for logging messages. intended to be "client" or "server"
  static const char* const _logFile; ///< file path for the log file
  static const char* const _tab;   ///< defines a tabulator for formatting
};

#endif // BATTLESHIP_LOGGER_H
