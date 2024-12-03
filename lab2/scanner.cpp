#include "scanner.hpp"
#include "UserInterface.hpp"
#include "forth.hpp"
#include <cctype>

/*

NO KEYWORDS, COMMANDS MAKES THEMSELFES

SCANNER READ TOKEN - RUN FABRIC TO GENERATE AN EXPRESSION
Token.hpp"
#include "forth.hpp"
#include <unordered_map>
*/

// const std::unordered_map<std::string, TokenType> Scanner::keywords = {
//     {"swap",    TokenType::SWAP},
//     {"dup",  TokenType::DUP},
//     {"drop",   TokenType::DROP},
//     {"false",  TokenType::FALSE},
//     {"for",    TokenType::FOR},
//     {"if",     TokenType::IF},
//     {"nil",    TokenType::NIL},
//     {"or",     TokenType::OR},
//     {"over",     TokenType::OVER},
//     {"emit",     TokenType::EMIT},
//     {"cr",     TokenType::CR},
//     {"do",     TokenType::DO},
//     {"loop",     TokenType::LOOP},
// };

std::vector<Token> Scanner::scanTokens() {
  while (!isAtEnd()) {
    start = current;
    scanToken();
  }
  tokens.push_back(Token(TokenType::END, "", "", line));
  return tokens;
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
  case '.':
    addToken(match('"') ? TokenType::DQUOTS : TokenType::DOT);
    break;
  case '\"':
    // str();
    addToken(TokenType::STRING, "\"");
    break;
  case ' ':
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
  }
  else {
  string text = source.substr(start, current);
  addToken(TokenType::IDENTIFIER);
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
    // Forth::error(line, "Can't determine string"); < shut
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
