//
// Created by nico on 04.05.23.
//

#include "Logger.h"
#include <sstream>

const char* const Logger::_logFile = "log.txt";
const char* const Logger::_tab     = "  "; // 2 spaces
std::string Logger::_prefix = "";

std::string Logger::getCurrentDateTime() {
  auto time = std::time(nullptr);
  auto locTime = *std::localtime(&time);
  std::ostringstream oss;
  oss << std::put_time(&locTime, "%d-%m-%Y %H:%M:%S");
  return oss.str();
}

void Logger::log(const std::string &message, const std::string &func) {
  std::stringstream output;
  const std::string function = "[" + func + "]"; // format function name
  output << _prefix << _tab << std::left << std::setw(18) << function << message; // build message
  std::cout << output.str() << std::endl; // write to console
  std::ofstream out; // write to log file
  try {
    out.open(_logFile, std::ios_base::app);
    out << getCurrentDateTime() << _tab << output.str() << std::endl; // we only need time in log file
    out.close();
  } catch (const std::ofstream::failure& e) {
    std::cout << "ERROR: Could not open/write to log file" << std::endl;
  }
}

void Logger::log(const BattleshipException &exception) {
  log(exception.what(), "BattleshipException");
}

void Logger::setPrefix(const std::string &s) {
  Logger::_prefix = s;
}
