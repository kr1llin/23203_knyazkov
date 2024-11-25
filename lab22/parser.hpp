#pragma once
#include "expressions.hpp"
#include "Token.hpp"

#include <memory>
#include <stdexcept>
#include <vector>

//parse tokens into expressions 
//literals are from parser
class Parser{
public:
  Parser(std::vector<Token> &tokens, Forth &forth) : tokens(tokens), forth(forth) {};
  std::unique_ptr<Expr> parse();
  std::unique_ptr<Expr> expression();

private:
  std::vector<Token> tokens;
  size_t current = 0;
  Forth &forth;

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

  bool match(const std::initializer_list<TokenType> &types);

  bool check(TokenType type);

  const Token& advance();

  bool isAtEnd() const;

  const Token& peek() const;

  // Get the previous token
  const Token& previous() const;

  void synchronize();

  class ParseError : std::runtime_error {
  public:
    // Constructor that takes a message
    explicit ParseError(const std::string &message)
        : std::runtime_error(message) {}
  };

  ParseError *error(Token &token, const string &message);

};
