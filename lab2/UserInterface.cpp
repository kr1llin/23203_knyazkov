#include "UserInterface.hpp"

void UserInterface::printStack(const Forth &forth) const {
  const std::vector<int> &stack = forth.getStack();
  for (auto i : stack) {
    std::cout << i << " ";
  }
  std::cout << "<- Top" << std::endl;
}

void UserInterface::displayMessage(const std::string &message) {
  std::cout << "< ";
  std::cout << message << std::endl;
}

 std::string UserInterface::getUserInput() {
   std::cout << "> ";
   std::string input;
   std::getline(std::cin, input);
   return input;
  }
