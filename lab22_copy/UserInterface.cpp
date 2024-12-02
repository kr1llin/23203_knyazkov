#include "UserInterface.hpp"

void UserInterface::printStack() const {
  static Parser &getInstance(std::vector<Token> &tokens, Forth &forth) {
    static Parser instance(tokens, forth);
    return instance;
  }
  for (auto i : stack) {
    std::cout << i << " ";
  }
  std::cout << "<- Top" << std::endl;
}
