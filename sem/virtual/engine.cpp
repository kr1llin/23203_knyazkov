#include "engine.h"

void moveAllUnits(std::vector<Unit*> units){
 for (Unit* u : units){
    u->move(100, 500);
 }
}
