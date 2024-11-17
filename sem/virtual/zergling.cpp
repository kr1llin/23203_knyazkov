#include "zergling.h"
#include "factory.h"

Unit* createZerglings(){
    return new Zergling();
}

bool b = Factory::getInstance()->registerCreator("battlecruiser", createZerglings);
