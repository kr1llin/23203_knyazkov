#include "parser.hpp"
#include "Token.hpp"
#include "expressions.hpp"

//*=======EXPRESSIONS========*//

//get token - make expression
Expr* Parser::parse() {
  try {
    return expression();
  } catch (Parser::ParseError error) {
    std::cerr << "Parse error!" << std::endl;
    return nullptr;
  }
}

// Функция для преобразования лексемы в целое число
    int parseNumber(const std::string& lexeme) {
        try {
            // Преобразуем строку в целое число
            return std::stoi(lexeme);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Ошибка: недопустимое число '" << lexeme << "'" << std::endl;
            throw; // Пробрасываем исключение дальше
        } catch (const std::out_of_range& e) {
            std::cerr << "Ошибка: число '" << lexeme << "' выходит за пределы диапазона" << std::endl;
            throw; // Пробрасываем исключение дальше
        }
    }
    
//ОН ПРИНИМАЕТ ТОЛЬКО ПО ОДНОМУ ЧИСЛУ СДЕЛАЙ ТАК ЧТОБЫ ОН ЖРАЛ ВСЕ СРАЗУ!!!
    void parseAllNumbers();

Expr* Parser::expression() {
    if (check(TokenType::NUMBER)) {
        return new PushNumberExpr(parseNumber(tokens[current].getLexeme())); 
    }
    if (check(TokenType::DUP)) {
        return new DupExpr();
    }
    if (check(TokenType::DROP)) {
        return new DropExpr();
    }

    if (check(TokenType::PLUS)) {
      return new SumExpr();
    }

    current++;
    // Add more commands as needed
    // Handle errors if no valid expression is found
    throw ParseError("Unexpected token");
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

const Token& Parser::advance() {
  if (!isAtEnd()) {
    current++;
  }
  return previous();
}

// bool Parser::isAtEnd() const { return (peek().getType() == TokenType::END); }
bool Parser::isAtEnd() const { return (current == tokens.size()); }


const Token& Parser::peek() const {
  if (isAtEnd()) {
    throw std::out_of_range("Attempted to peek at the end of the token list");
  }
  return tokens[current];
}

const Token& Parser::previous() const {
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
