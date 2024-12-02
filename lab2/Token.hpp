#pragma once

#include <string>

using string = std::string;

// dictionary
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
    return std::to_string(static_cast<int>(type)) + " " + lexeme + " " + literal;
  }

  Token(TokenType type, const string& lexeme, const string& literal, int line)
      : type(type), lexeme(lexeme),literal(literal), line(line) {}

  Token(const Token& other)
      : type(other.type), lexeme(other.lexeme),literal(other.literal), line(other.line) {}

  Token(Token&& other) noexcept
      : type(other.type), lexeme(std::move(other.lexeme)), literal(std::move(other.literal)), line(other.line) {}

  Token &operator=(const Token &other){
    if (this == &other) {
      return *this;
    }
    type = other.getType();
    lexeme = other.getLexeme();
    literal = other.getLiteral();
    line = other.getLine();
    return *this;
  }
      

private:
  TokenType type;
  string lexeme;
  string literal; // ??? it represents something that we can use later??
  int line;
};
