#include "parser.hpp"
#include "Token.hpp"
#include "expressions.hpp"
#include "factory.hpp"
#include <memory>
#include <ostream>
#include <vector>

//*=======EXPRESSIONS========*//

std::vector<Token>& Parser::getTokens(){
  return tokens;
}
size_t Parser::getCurrent() const{
  return current; 
}

// get token - make expression - excecute
//VECTOR OF UNIQUE POINTERS -- STUPIDO!!!!!
void Parser::parse() {
  while (!check(TokenType::END)) {
    std::cout << "Parsing!" << std::endl;
     std::unique_ptr<Expr> expression = getExpression();
     expression->execute(forth, tokens);
  }
}

 std::unique_ptr<Expr> Parser::getExpression(){
   std::unique_ptr<Expr> expression;
   try {
       if (!check(TokenType::NIL)) {
         TokenType type = peek().getType();
         expression = Factory<TokenType, Expr>::getInstance()->createCommandByName(type, current);
         std::cout << "Cur token in parser is " << tokens[current].getLexeme()
                   << std::endl;
       } else {
         throw ParseError("Unexpected token");
       }
   } catch (Parser::ParseError error) {
     std::cerr << "Parse error!" << std::endl;
     return std::unique_ptr<Expr>(); // empty vector
   }
   return expression; // empty vector
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

//DUMPSTER

//for parse

    // if (check(TokenType::NUMBER)) {
    //   int number = parseNumber(tokens[current].getLexeme());
    //    expr =
    //       Factory<std::string, Expr>::getInstance()->createCommandByName(
    //           "number", number);
    // }
    // else if (!check(TokenType::NIL)) {
    //   std::string commandName = peek().getLexeme();
    //   expr =
    //       Factory<std::string, Expr>::getInstance()->createCommandByName(
    //           commandName);
    // } else {
    //   throw ParseError("Unexpected token");
    // }
    // current++;
    // return expr;

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
