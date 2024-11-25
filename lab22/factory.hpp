
#pragma once

#include "expressions.hpp"

#include <functional>
#include <string>
#include <map>
#include <memory>


template <class Key, class Product>
class Factory {
public:
    static Factory* getInstance() {
        static Factory instance;
        return &instance;
    }

    std::unique_ptr<Product> createCommandByName(const Key& name) {
        auto command = commands_.find(name);
        if (command == commands_.end()) {
            throw std::runtime_error("Command not found: " + name);
        }
        return command->second(); // Call the creator function
    }

    bool registerCreator(const Key& name, std::function<std::unique_ptr<Product>()> creator) {
        commands_[name] = creator;
        return true;
    }

private:
    std::map<Key, std::function<std::unique_ptr<Product>()>> commands_;
};

namespace {
static bool regMult =
        Factory<std::string, Expr>::getInstance()->registerCreator(
            "mul", []() { return std::make_unique<MultExpr>(); });
static bool regSum =
    Factory<std::string, Expr>::getInstance()->registerCreator(
        "+", []() { return std::make_unique<SumExpr>(); });
}
