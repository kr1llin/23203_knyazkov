#include "parser.hpp"
#include "Token.hpp"
#include "expressions.hpp"

//*=======EXPRESSIONS========*//

//get token - make expression
Expr* Parser::parse() {
  try {
    return expression();
  } catch (Parser::ParseError error) {
    return nullptr;
  }
}

bool Parser::match(const std::initializer_list<TokenType> &types) {
  for (TokenType type : types) {
    if (check(type)) {
      advance();
      return true;
    }
  }
  return false;
}

bool Parser::check(TokenType type) {
  if (isAtEnd())
    return false;
  return peek().getType() == type;
}

Token Parser::advance() {
  if (!isAtEnd()) {
    current++;
  }
  return previous();
}

bool Parser::isAtEnd() const { return (peek().getType() == TokenType::END); }

Token Parser::peek() const {
  if (isAtEnd()) {
    throw std::out_of_range("Attempted to peek at the end of the token list");
  }
  return tokens[current];
}

Token Parser::previous() const {
  if (current == 0) {
    throw std::out_of_range("No previous token available.");
  }
  return tokens[current - 1];
}

//if error - run to the end of expression
void Parser::synchronize() {
  advance();

  while (!isAtEnd()) {
    if (previous().getType() == TokenType::SEMICOLON)
      return;

    switch (peek().getType()) {
    case TokenType::FOR:
    case TokenType::IF:
    case TokenType::WHILE:
    case TokenType::DQUOTS:
      return;
    default:
      break;
    }
    advance();
  }
}
