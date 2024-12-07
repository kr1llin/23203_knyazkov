#include "scanner.hpp"
#include "Token.hpp"
#include "UserInterface.hpp"
#include "forth.hpp"
#include <cctype>
#include <stdexcept>
#include <string>

std::vector<Token> Scanner::scanTokens() {
  while (!isAtEnd()) {
    start = current;
    scanToken();
  }
  tokens.push_back(Token(TokenType::END, "", "", line));
  return tokens;
}

void Scanner::addWhiteSpaces(){
  while (peek() == ' ') {
    advance();
  }
  string spaces = source.substr(start, current - start);
  addToken(TokenType::WHITESPACE, spaces);
}

void Scanner::scanToken() {
  char c = advance();
  switch (c) {
  case '(':
    addToken(TokenType::LEFT_PAREN);
    break;
  case ')':
    addToken(TokenType::RIGHT_PAREN);
    break;
  case '{':
    addToken(TokenType::LEFT_BRACE);
    break;
  case '}':
    addToken(TokenType::RIGHT_BRACE);
    break;
  case ',':
    addToken(TokenType::COMMA);
    break;
  case '-':
    addToken(TokenType::MINUS);
    break;
  case '+':
    addToken(TokenType::PLUS);
    break;
  case ';':
    addToken(TokenType::SEMICOLON);
    break;
  case '*':
    addToken(TokenType::STAR);
    break;
  case '/':
    addToken(TokenType::SLASH);
    break;
  case '>':
  case '<':
  case '=':
    addToken(TokenType::LOGIC);
    break;
  case '.':
    addToken(match('"') ? TokenType::DQUOTS : TokenType::DOT);
    break;
  case '\"':
    // str();
    addToken(TokenType::QUOTS, "\"");
    break;
  case ' ':
    addWhiteSpaces();
  case '\r':
  case '\t':
    break;
  case '\n':
    line++;
    break;
  default:
    if (std::isdigit(c)) {
      number();
    } else if (std::isalpha(c)) {
      identifier();
    } else {
      // Forth::error(line, "???");
    }
    break;
  }
}

void Scanner::number() {
  while (std::isdigit(peek())) {
    advance();
  }
  addToken(TokenType::NUMBER, source.substr(start, current));
}

bool Scanner::isAlphaNumeric(char c) {
  return std::isalpha(c) || std::isdigit(c);
}

//it can be command or variable or something else
void Scanner::identifier() {
  while (isAlphaNumeric(peek())) {
    advance();
  }
  if (peek() == '\"') {
    advance();
    string text = source.substr(start, current - start - 1);
    addToken(TokenType::STRING, text);
    addToken(TokenType::QUOTS, "\"");

  }
  else {
  string text = source.substr(start, current);
  addToken(TokenType::IDENTIFIER, text);
  }
}

// void Scanner::forthString(){
//    while (peek() != '\"' && !isAtEnd()) {
//     advance();
//   }
//   string text = source.substr(start, current - start);

//   if (peek() == '\"') {
//     advance();
//     addToken(TokenType::STRING, text);
// }
// }

void Scanner::str() {
  int sizeStr = 0;
  while ((peek() != '"') && (!isAtEnd())) {
    if (peek() == '\n') {
      line++;
    }
    sizeStr++;
    advance();
  }

  if (isAtEnd()) {
    throw std::runtime_error("Can't determine string at line " + std::to_string(line)); 
    return;
  }

  advance(); // second ""
  string value = source.substr(start + 1, sizeStr);
  addToken(TokenType::STRING, value);
}

// conditional advance
bool Scanner::match(char expected) {
  if (isAtEnd()) {
    return false;
  }
  if (source.at(current) != expected) {
    return false;
  }
  current++;
  return true;
}

// lookahead
char Scanner::peek() {
  if (isAtEnd()) {
    return '\0';
  }
  return source.at(current);
}

char Scanner::peekNext() {
  if (current + 1 >= source.length()) {
    return '\0';
  }
  return source.at(current + 1);
}

bool Scanner::isAtEnd() { return (current >= source.length()); }

// for input
char Scanner::advance() { return source[current++]; }

void Scanner::addToken(TokenType type) { addToken(type, {}); }

void Scanner::addToken(TokenType type, string literal) {
  string text = source.substr(start, current - start);
  tokens.push_back(Token(type, text, literal, line));
}
