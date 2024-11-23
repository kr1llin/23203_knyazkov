#pragma once

#include "Token.hpp"
#include <unordered_map>
#include <vector>

//find tokens from input string
class Scanner{
  public:
    Scanner(const string& source) : source(source){}
    std::vector<Token> scanTokens();
    void scanToken();
    void addToken(TokenType type);
    void addToken(TokenType type, string literal);

    // static const TokenType getKeyWordType(string key) {
    //   auto index = keywords.find(key);
    //   if (index != keywords.end()) {
    //     return index->second;
    //   }
    //   return TokenType::NIL; // NIL = wasn't found
    // }

  private:  
    bool isAtEnd();
    void str();
    void number();
    void identifier();
    bool isAlphaNumeric(char c);
    char advance();
    char peek();
    char peekNext();
    bool match(char expected);

    int start; //points to the first character in the lexeme being scanned
    int current; //character currently scanned
    int line = 1; //source line (that current is currently scanning)

    const string source;
    std::vector<Token> tokens; //new array list

    static const std::unordered_map<std::string, TokenType> keywords;
};
