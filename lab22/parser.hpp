#pragma once
#include "expressions.hpp"
#include "Token.hpp"

#include <stdexcept>
#include <vector>

//parse tokens into expressions 
//literals are from parser
class Parser {
public:
  Parser(const std::vector<Token> &tokens) : tokens(tokens) {};
  Expr* parse();

private:
  const std::vector<Token> tokens;
  size_t current = 0;

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

  Token advance();

  bool isAtEnd() const;

  Token peek() const;

  // Get the previous token
  Token previous() const;

  void synchronize();

  class ParseError : std::runtime_error {
  public:
    // Constructor that takes a message
    explicit ParseError(const std::string &message)
        : std::runtime_error(message) {}
  };

  ParseError *error(Token &token, const string &message);

};
