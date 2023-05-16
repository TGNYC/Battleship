//
// Created by nico on 04.05.23.
//

#include "Logger.h"

const char* const Logger::logFile = "log.txt";
const char* const Logger::tab = "    "; // 4 spaces
std::string Logger::prefix = "      "; // 6 spaces

std::string Logger::getCurrentDateTime() {
  auto t = std::time(nullptr);
  auto tm = *std::localtime(&t);
  std::ostringstream oss;
  oss << std::put_time(&tm, "%d-%m-%Y %H:%M:%S");
  return oss.str();
}

void Logger::log(const std::string& message, Logger::Type type) {
  // write to console
  std::cout << tab << prefix << tab << message << std::endl;
  // write to log file
  std::ofstream file;
  try {
    file.open(logFile, std::ios_base::app);
    file << getCurrentDateTime() << tab << prefix << tab << message << std::endl;
    file.close();
  } catch (const std::ofstream::failure& e) {
    std::cout << "Error: Could not open/write to log file" << std::endl;
  }
}

void Logger::log(const BattleshipException &exception) {
  log(exception.what(), Type::Error);
}

void Logger::setPrefix(const std::string &s) {
  Logger::prefix = s;
}

