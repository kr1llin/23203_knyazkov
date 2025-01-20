
#pragma once

#include "UserInterface.hpp"

#include <cctype>
#include <functional>
#include <map>
#include <memory>
#include <string>

class Expr;

template <class Key, class Product> class Factory {
public:
  Factory(const Factory &) = delete;
  Factory &operator=(const Factory &) = delete;
  
  static Factory *getInstance() {
    static Factory instance;
    return &instance;
  }

  std::unique_ptr<Product> createCommandByName(const Key &key) {
    auto command = commands_.find(key);
    if (command == commands_.end()) {
      UserInterface::displayMessage("?");
      return {};
      // throw std::runtime_error("Command not found");
    }
    return command->second(); // return creator for function
  }

  bool registerCreator(const Key &key,
                       std::function<std::unique_ptr<Product>()> creator) {
    commands_[key] = creator;
    return true;
  }

private:
  std::map<Key, std::function<std::unique_ptr<Product>()>> commands_;
  Factory() = default;
};

template <class Key, class Product> struct Creator {
  explicit Creator(const Key key){
    Factory<Key, Expr>::getInstance()->registerCreator(
    key, []() { return std::make_unique<Product>(); });
  }
};

