#include "battlecruiser.h"
#include "factory.h"


Unit* createBattlecruiser(){
    return new BattleCruiser();
}

bool b = Factory::getInstance()->registerCreator("battlecruiser", createBattlecruiser);
