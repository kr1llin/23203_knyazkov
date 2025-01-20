#pragma once

#include <string>
#include <vector>

//only console mode
class UserInterface {
public:

  // static UserInterface &getInstance() {
  //   static UserInterface instance;
  //   return instance;
  // }

  UserInterface(const UserInterface &) = delete;
  UserInterface &operator=(const UserInterface &) = delete;
  
  static void printStack(const std::vector<int> &stack);
  static void displayMessage(const std::string &message);
  static std::string getUserInput();

private:
  UserInterface() {}
};
