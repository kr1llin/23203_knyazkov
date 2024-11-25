#include "parser.hpp"
#include "Token.hpp"
#include "expressions.hpp"
#include "factory.hpp"
#include <cstddef>
#include <memory>

//*=======EXPRESSIONS========*//

int parseNumber(const std::string &lexeme) {
  try {
    return std::stoi(lexeme);
  } catch (const std::invalid_argument &e) {
    std::cerr << "Error: invalid  '" << lexeme << "'" << std::endl;
    throw;
  } catch (const std::out_of_range &e) {
    std::cerr << "Error: number '" << lexeme << "' out of range" << std::endl;
    throw;
  }
}

// get token - make expression
std::unique_ptr<Expr> Parser::parse() {
  try {
    std::unique_ptr<Expr> expr = nullptr;

    if (check(TokenType::NUMBER)) {
      int number = parseNumber(tokens[current].getLexeme());
       expr =
          Factory<std::string, Expr>::getInstance()->createCommandByName(
              "number", number);
    }
    else if (!check(TokenType::NIL)) {
      std::string commandName = peek().getLexeme();
      expr =
          Factory<std::string, Expr>::getInstance()->createCommandByName(
              commandName);
    } else {
      throw ParseError("Unexpected token");
    }

    current++;
    return expr;

  } catch (Parser::ParseError error) {
    std::cerr << "Parse error!" << std::endl;
    return nullptr;
  }
}

// std::unique_ptr<Expr> Parser::expression() {
//     if (check(TokenType::NUMBER)) {
//       forth.push(parseNumber(tokens[current].getLexeme()));
//     }
//     else if (!check(TokenType::NIL)) {
//         std::string commandName = peek().getLexeme();
//             std::unique_ptr<Expr> expr = Factory<std::string,
//             Expr>::getInstance()->createCommandByName(commandName); return
//             expr; // Return the raw pointer
//     } else {
//       throw ParseError("Unexpected token");
//     }

//     current++;
// }

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

const Token &Parser::advance() {
  if (!isAtEnd()) {
    current++;
  }
  return previous();
}

// bool Parser::isAtEnd() const { return (peek().getType() == TokenType::END); }
bool Parser::isAtEnd() const { return (current == tokens.size()); }

const Token &Parser::peek() const {
  if (isAtEnd()) {
    throw std::out_of_range("Attempted to peek at the end of the token list");
  }
  return tokens[current];
}

const Token &Parser::previous() const {
  if (current == 0) {
    throw std::out_of_range("No previous token available.");
  }
  return tokens[current - 1];
}

// if error - run to the end of expression
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
