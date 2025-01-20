#pragma once
#include "forth.hpp"
#include <string>

class UserInterface {
public:

  static UserInterface &getInstance() {
    static UserInterface instance;
    return instance;
  }

  UserInterface(const UserInterface &) = delete;
  UserInterface &operator=(const UserInterface &) = delete;
  void printStack(const Forth &forth) const;
  void displayMessage(const std::string &message);
  std::string getUserInput() ;

private:
  UserInterface() {}
};
