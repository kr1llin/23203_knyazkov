
#pragma once

#include "expressions.hpp"

#include <functional>
#include <optional>
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

    std::unique_ptr<Product> createCommandByName(const Key& name, std::optional<int> arg = std::nullopt) {
        auto command = commands_.find(name);
        if (command == commands_.end()) {
            throw std::runtime_error("Command not found: " + name);
        }
        return command->second(arg); // calling creator for function
    }

    bool registerCreator(const Key& name, std::function<std::unique_ptr<Product>(std::optional<int>)> creator) {
        commands_[name] = creator;
        return true;
    }

private:
    std::map<Key, std::function<std::unique_ptr<Product>(std::optional<int>)>> commands_;
};

namespace {
static bool regMult =
        Factory<std::string, Expr>::getInstance()->registerCreator(
            "mul", [](std::optional<int> arg) { 
                return std::make_unique<MultExpr>(); 
            });
static bool regSum =
    Factory<std::string, Expr>::getInstance()->registerCreator(
        "+", [](std::optional<int> arg) { 
            return std::make_unique<SumExpr>(); 
        });

static bool regNumber =
    Factory<std::string, Expr>::getInstance()->registerCreator(
        "number", [](std::optional<int> arg) { 
            if (!arg.has_value()) {
                throw std::runtime_error("No argument for 'number' command!");
            }
            return std::make_unique<PushNumberExpr>(arg.value()); 
        });
}
