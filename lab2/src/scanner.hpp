#pragma once

#include "Token.hpp"
#include <unordered_map>
#include <vector>

// find tokens from input string
class Scanner {
public:
  Scanner(const string &source) : source(source) {}
  std::vector<Token> scanTokens();
  void scanToken();
  void addToken(TokenType type);
  void addToken(TokenType type, string literal);

private:
  bool isAtEnd();
  void forthString();
  void str();
  void number();
  void identifier();
  bool isAlphaNumeric(char c);
  char advance();
  char peek();
  void addWhiteSpaces();
  char peekNext();
  bool match(char expected);

  int start; // start of lexeme being scanned
  int current;
  int line = 1; // source line (that current is currently scanning)

  const string source;
  std::vector<Token> tokens;

  static const std::unordered_map<std::string, TokenType> keywords;
  };
