#pragma once

#include "value.hpp"
#include <regex>
#include <string>
#include <variant>
#include <vector>

using string = std::string;

// I use this as dictionary
enum class TokenType {
  // Single-character tokens.
  LEFT_PAREN,
  RIGHT_PAREN,
  LEFT_BRACE,
  RIGHT_BRACE,
  DQUOTS,
  COMMA,
  DOT,
  MINUS,
  PLUS,
  SEMICOLON,
  SLASH,
  STAR,
  MOD,
  I, // i is for loops

  // COMMANDS
  DUP,
  DROP,
  SWAP,
  ROT,
  OVER,
  EMIT,
  CR,
  DOTQUOTE,
  LOOP,
  DO,

  // One or two character tokens.
  BANG,
  BANG_EQUAL,
  EQUAL,
  EQUAL_EQUAL,
  GREATER,
  GREATER_EQUAL,
  LESS,
  LESS_EQUAL,

  // Literals.
  IDENTIFIER,
  STRING,
  NUMBER,

  // Keywords.
  AND,
  ELSE,
  FALSE,
  FOR,
  IF,
  END,
  NIL,
  OR,
  PRINT,
  THIS,
  TRUE,
  VAR,
  WHILE,
  DUMMY,
};

class Token {
public:
  TokenType getType() const {return type;}
  string getLexeme() const {return lexeme;}
  string getLiteral() const {return literal;}
  int getLine() const {return line;}

  string toString() const {
    return std::to_string(static_cast<int>(type)) + " " + lexeme + " " +
           literal;
  }

  Token(TokenType type, const string lexeme, const string literal,
        const int line)
      : type(type), lexeme(lexeme), literal(literal), line(line) {}

private:
  TokenType type;
  string lexeme;
  Value literal; // ??? it represents something that we can use later. Number, string, boolean or expression (command)
  int line; // where token appeared
};
