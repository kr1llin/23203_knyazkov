#include "UserInterface.hpp"


 void UserInterface::printStack(const Forth& forth) const {
        const std::vector<int>& stack = forth.getStack();
        for (auto i : stack) {
            std::cout << i << " ";
        }
        std::cout << "<- Top" << std::endl;
    }
