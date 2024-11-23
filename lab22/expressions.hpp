#pragma once
#include "Token.hpp"
#include "forth.hpp"

#include <iostream>
#include <memory>
#include <stack>


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


class Expr{
public:
    virtual ~Expr() = default;
    virtual void execute(Forth&) = 0;

};

class PushNumberExpr : public Expr {
public:
    PushNumberExpr(int value) : value(value) {}
    void execute(Forth& forth) override;
private:
    int value;
};

class DupExpr : public Expr {
public:
    void execute(Forth& forth) override;
};

class DropExpr : public Expr {
  public:
    void execute(Forth& forth) override ;
};

class SumExpr : public Expr {
  public:
    void execute(Forth& forth) override;
  private:
    int left;
    int right;
};

//+ - / * mod
class Arithmetical : public Expr {
public:
  Arithmetical(Expr *left, Expr *right, TokenType operatorToken)
      : left(left), right(right), operatorToken(operatorToken) {}

  void execute(Forth& forth) override ;

private:
  Expr *left;
  TokenType operatorToken;
  Expr *right;
};
