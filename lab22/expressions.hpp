#pragma once
#include "Token.hpp"

#include <iostream>
#include <memory>


///==== COMMANDS ====///
// make fabric here //



// //return value of expression (currently only number (int))
// class Object {
// public:
//     virtual ~Object() = default;
// };

// class Number : public Object {
// public:
//     explicit Number(int value) : value(value) {}
//     int value;
// };

class Expr {
public:
    virtual ~Expr() = default;
    virtual void execute() const = 0;

};

//+ - / * mod
class Arithmetical : public Expr {
public:
  Arithmetical(Expr *left, Expr *right, TokenType operatorToken)
      : left(left), right(right), operatorToken(operatorToken) {}

  void execute() const override {
    // Evaluating arithmetical expression
  }

  Token getOperatorToken() { return operatorToken; }

private:
  Expr *left;
  Token operatorToken;
  Expr *right;
};
