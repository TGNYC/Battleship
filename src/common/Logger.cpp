//
// Created by nico on 04.05.23.
//

#include "Logger.h"

const char* const Logger::logFile = "log.txt";

std::string Logger::getCurrentDateTime() {
  auto t = std::time(nullptr);
  auto tm = *std::localtime(&t);
  std::ostringstream oss;
  oss << std::put_time(&tm, "%d-%m-%Y %H:%M:%S");
  return oss.str();
}

void Logger::log(const std::string& message, Logger::Type type) {
  std::ofstream file;
  try {
    file.open(logFile, std::ios_base::app);
    file << getCurrentDateTime() << "    " << message << std::endl;
    file.close();
  } catch (const std::ofstream::failure& e) {
    std::cout << "Error: Could not open/write to log file" << std::endl;
  }
}

void Logger::log(const BattleshipException &exception) {
  log(exception.what(), Type::Error);
}