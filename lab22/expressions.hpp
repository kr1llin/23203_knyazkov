#pragma once
#include "forth.hpp"



///==== COMMANDS ====///

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
};

class SubsExpr : public Expr {
  public:
    void execute(Forth& forth) override;
};

class ModExpr : public Expr {
  public:
    void execute(Forth& forth) override;
};

class SlashExpr : public Expr {
  public:
    void execute(Forth& forth) override;
};

class MultExpr : public Expr {
  public:
    void execute(Forth& forth) override;
  private:
};

// //+ - / * mod
// class Arithmetical : public Expr {
// public:
//   Arithmetical(Expr *left, Expr *right, TokenType operatorToken)
//       : operatorToken(operatorToken) {}

//   void execute(Forth& forth) override ;

// private:
//   TokenType operatorToken;
// };
