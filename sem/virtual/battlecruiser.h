#include "unit.h"
#include <iostream>

class BattleCruiser : public Unit {
public:
  void move(int x, int y) override {
    std::cout << "BattleCruiser move!" << std::endl;
  }
  void attack(int x, int y) override {
    std::cout << "BattleCruiser attack!" << std::endl;
  }
  Unit *createBattleCruiser() { return new BattleCruiser(); }
};
