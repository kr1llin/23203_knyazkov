#include "unit.h"
#include <iostream>

class Zergling : public Unit {
public:
  void move(int x, int y) override {
    std::cout << "Zergling move!" << std::endl;
  }
  void attack(int x, int y) override {
    std::cout << "Zergling attack!" << std::endl;
  }
  
  Unit* createZergling() {
    return new Zergling();
}
};
