#pragma once

#include "ExecutionContext.hpp"
#include "expressions.hpp"
#include "Token.hpp"

#include <memory>
#include <stdexcept>
#include <unordered_set>

//Interprete tokens into expressions
class Interpreter{
public:
  explicit Interpreter(ExecutionContext* context) : context(context){}
  std::unique_ptr<Expr> getExpression();
  void interprete();
  void executeExpr();
  std::unique_ptr<Expr> expression();
  bool isInIgnoreList(Token &token) ;

private:
  class InterpreterError : std::runtime_error {
  public:
    explicit InterpreterError(const std::string &message)
        : std::runtime_error(message) {}
  };

  InterpreterError *error(Token &token, const string &message);
  ExecutionContext* context;
};

const std::unordered_set<TokenType> ignoreTypeList = {
    TokenType::WHITESPACE, TokenType::SEMICOLON};

const std::unordered_set<std::string> ignoreLexemeList = {
    "loop", "then"};
