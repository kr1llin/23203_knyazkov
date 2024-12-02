
#pragma once

#include "Token.hpp"
#include "expressions.hpp"

#include <cctype>
#include <functional>
#include <map>
#include <memory>
#include <string>


template <class Key, class Product> class Factory {
public:
  static Factory *getInstance() {
    static Factory instance;
    return &instance;
  }

  std::unique_ptr<Product> createCommandByName(const Key &key, int tokenNumber) {
    auto command = commands_.find(key);
    if (command == commands_.end()) {
      throw std::runtime_error("Command not found");
    }
    return command->second(tokenNumber); // return creator for function
  }

  bool registerCreator(const Key& key,
                       std::function<std::unique_ptr<Product>(int tokenNum)> creator) {
    commands_[key] = creator;
    return true;
  }

private:
  std::map<Key, std::function<std::unique_ptr<Product>(int tokenNum)>> commands_;
};


namespace {
static bool regMult =
    Factory<std::string, Expr>::getInstance()->registerCreator(
        "*", [](int) { return std::make_unique<MultExpr>(); });
static bool regSum = Factory<std::string, Expr>::getInstance()->registerCreator(
    "+", [](int) { return std::make_unique<SumExpr>(); });
static bool regNumber =
    Factory<TokenType, Expr>::getInstance()->registerCreator(
        TokenType::NUMBER, [](int tokenNumber) {
          return std::make_unique<PushNumberExpr>(tokenNumber);
        });
static bool regDup = Factory<std::string, Expr>::getInstance()->registerCreator(
    "dup", [](int tokenNumber) { return std::make_unique<DupExpr>(); });
static bool regStringOutput =
    Factory<std::string, Expr>::getInstance()->registerCreator(
        ".\"", [](int tokenNumber) {
          return std::make_unique<PrintStrExpr>(tokenNumber);
        });
static bool regSlash =
    Factory<std::string, Expr>::getInstance()->registerCreator(
        "/", [](int tokenNumber) {
          return std::make_unique<SlashExpr>();
        });
static bool regEmit =
    Factory<std::string, Expr>::getInstance()->registerCreator(
        "emit", [](int tokenNumber) { return std::make_unique<EmitExpr>(); });
} 
