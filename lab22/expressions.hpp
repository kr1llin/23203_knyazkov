#pragma once
#include "forth.hpp"
#include "Token.hpp"
#include <vector>



///==== COMMANDS ====///

/* 
  Expr *expression();
  Expr *equality();
  Expr *comparison();
  Expr *term();
  Expr *factor();
  Expr *unary();
  Expr *primary();
  Expr *swap();
  Expr *over();
  Expr *emit();
  Expr *drop();
  Expr *dup();
  Expr *dot();
  */

class Expr{
public:
    virtual ~Expr() = default;
    virtual void execute(Forth&, std::vector<Token>& tokens) = 0;
};

class PushNumberExpr : public Expr {
public:
    PushNumberExpr(int tNumber) : tokenNumber(tNumber){};
    void execute(Forth& forth, std::vector<Token>& tokens) override;
private:
  int tokenNumber{};
};

class DupExpr : public Expr {
public:
    void execute(Forth& forth, std::vector<Token>& tokens) override;
};

class DropExpr : public Expr {
  public:
    void execute(Forth& forth, std::vector<Token>& tokens) override ;
};

class SumExpr : public Expr {
  public:
    void execute(Forth& forth, std::vector<Token>& tokens) override;
};

class SubsExpr : public Expr {
  public:
    void execute(Forth& forth, std::vector<Token>& tokens) override;
};

class ModExpr : public Expr {
  public:
    void execute(Forth& forth, std::vector<Token>& tokens) override;
};

class SlashExpr : public Expr {
  public:
    void execute(Forth& forth, std::vector<Token>& tokens) override;
};

class MultExpr : public Expr {
  public:
    void execute(Forth& forth, std::vector<Token>& tokens) override;
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
