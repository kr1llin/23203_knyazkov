
#pragma once

#include "Token.hpp"
#include "expressions.hpp"

#include <cctype>
#include <functional>
#include <map>
#include <memory>
#include <optional>
#include <string>


template <class Key, class Product> class Factory {
public:
  //singleton 
  static Factory *getInstance() {
    static Factory instance;
    return &instance;
  }

  std::unique_ptr<Product> createCommandByName(const TokenType &type, int tokenNumber) {
    if (type == TokenType::NIL || type == TokenType::END){
      throw std::runtime_error("Ouch");
    }
    auto command = commands_.find(type);
    if (command == commands_.end()) {
      throw std::runtime_error("Command not found");
    }
    return command->second(tokenNumber); // calling creator for function
  }

  bool registerCreator(const TokenType& type,
                       std::function<std::unique_ptr<Product>(int)> creator) {
    commands_[type] = creator;
    return true;
  }

private:
  std::map<TokenType, std::function<std::unique_ptr<Product>(int)>> commands_;
};

//MAKE THIS TEMPLATED somehomw...
//move to super class expression (default constructor)
namespace {
static bool regMult =
    Factory<TokenType, Expr>::getInstance()->registerCreator(
        TokenType::STAR, [](int) { return std::make_unique<MultExpr>(); });
static bool regSum = Factory<TokenType, Expr>::getInstance()->registerCreator(
    TokenType::PLUS, [](int) { return std::make_unique<SumExpr>(); });
static bool regNumber =
    Factory<TokenType, Expr>::getInstance()->registerCreator(
        TokenType::NUMBER, [](int tokenNumber) { return std::make_unique<PushNumberExpr>(tokenNumber); });
}
