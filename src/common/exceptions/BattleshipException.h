//
// Created by Tejas Gupta on 5/1/23.
//

#ifndef BATTLESHIP_BATTLESHIPEXCEPTION_H
#define BATTLESHIP_BATTLESHIPEXCEPTION_H

#include <string>

class BattleshipException : public std::exception {
private:
  std::string _msg;
public:
  explicit BattleshipException(const std::string& message) : _msg(message) { };

  const char* what() const noexcept override {
    return _msg.c_str();
  }
};

#endif //LAMA_LAMAEXCEPTION_H
