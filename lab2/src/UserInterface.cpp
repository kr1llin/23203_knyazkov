#include "UserInterface.hpp"
#include <iostream>


void UserInterface::printStack(const std::vector<int> &stack) {
  std::cout << "------------------------" << std::endl;

  for (auto i : stack) {
    std::cout << i << " ";
  }
  std::cout << "<- Top\n";
  std::cout << "------------------------" << std::endl;
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
