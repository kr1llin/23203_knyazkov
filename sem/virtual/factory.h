#pragma once
#include <string>
#include <map>
#include "unit.h"

class Factory {
public:
    static Factory* getInstance() {
        //
        return nullptr;
    }
    Unit* createUnitByName(std::string name){
        auto* creator = creators_.at(name);
        Unit* u = creator();
        return u;
    }

    bool registerCreator(const std::string& name, Unit* (*creator)()) {
        creators_[name] = creator;
    }

private:
    std::map<std::string, Unit* (*)()> creators_;
};
