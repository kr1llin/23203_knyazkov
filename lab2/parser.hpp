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
  static Parser &getInstance(std::vector<Token> &tokens, Forth &forth) {
    static Parser instance(tokens, forth);
    return instance;
  }

 std::unique_ptr<Expr> getExpression();

  void resetTokens(std::vector<Token> &newTokens) {
    tokens = newTokens;
    current = 0;
  }

  void parse();
  void executeExpr();
  std::vector<Token>& getTokens();
  void dropToken(size_t index);
  void placeCurrent(size_t index);
  Token getPreviousToken() const;
  Token getCurrentToken() const;
  size_t getCurrent() const;
  void moveCurrent() { current++; }
  std::unique_ptr<Expr> expression();

private:
  std::vector<Token> tokens;
  size_t current = 0;
  Forth &forth;

  Parser(std::vector<Token> &tokens, Forth &forth)
      : tokens(tokens), forth(forth) {};

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
