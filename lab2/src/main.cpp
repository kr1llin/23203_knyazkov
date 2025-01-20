#include "forth.hpp"
#include <iostream>

int main(int argc, const char **argv) {
  try {
    return Forth::executeForth(argc, argv);
  } catch (const std::exception &ex) {
    std::cerr << "forth: " << ex.what() << std::endl;
    return -1;
  }
}
