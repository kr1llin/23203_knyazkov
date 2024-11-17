#include <string>
#include <vector>
#include <iostream>

#include "engine.h"
#include "factory.h"
#include "zergling.h"
#include "battlecruiser.h"

Unit *createUnitByName(std::string_view name) {
    Unit* u = nullptr;
  if ((std::string("zergling") == name)) {
    u = new Zergling();
  } else if (std::string("battlecruiser") == name) {
    u = new BattleCruiser;
  }
  return u;
}

int main(int argc, char** argv) {
       if (argc < 2) {
        std::cerr << "gimme units" << std::endl;
        return -1;
    }

    Factory factory;
    factory.registerCreator("zergling", createZergling);
    factory.registerCreator("battlecruiser", createBattleCruiser);


    std::vector<Unit*> units;

    for (int i = 1; i < argc; ++i) {
        Unit* u = createUnitByName(argv[i]);
        units.push_back(u);
    }
    moveAllUnits(units);
}
