#pragma once
#include "forth.hpp"

#include <string>

class UserInterface {
public:

  static UserInterface &getInstance() {
    static UserInterface instance;
    return instance;
  }

  void printStack(const Forth &forth) const;
  UserInterface(const UserInterface &) = delete;
  UserInterface &operator=(const UserInterface &) = delete;
  void displayMessage(const std::string &message);
  std::string getUserInput() ;

private:
  UserInterface() {}
};
