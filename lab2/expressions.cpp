#include "expressions.hpp"
#include "UserInterface.hpp"
#include "Token.hpp"
#include "parser.hpp"

#include <string>


int parseNumber(const std::string &lexeme);

void DupExpr::execute(Forth &forth, std::vector<Token>& tokens) {
  int topValue = forth.peek();
  forth.push(topValue);
}

void DropExpr::execute(Forth &forth, std::vector<Token>& tokens) {forth.pop(); }

//Numbersss
void PushNumberExpr::execute(Forth &forth, std::vector<Token>& tokens) { 
  Parser& parser = Parser::getInstance(tokens, forth);
  int value = parseNumber(tokens[tokenNumber].getLexeme());
  forth.push(value); 
}

//."
void PrintStrExpr::execute(Forth &forth, std::vector<Token>& tokens) { 
  Parser& parser = Parser::getInstance(tokens, forth);
  Token curToken = tokens[parser.getCurrent()];

  if (curToken.getType() != TokenType::STRING){
    throw std::runtime_error("NO STRING AFTER .\"!!!");
  }
  else {
    //better to use user interface (forth.print)
    UserInterface::getInstance().displayOutput(curToken.getLiteral());
    // std::cout << "< " << curToken.getLiteral() << std::endl;
  }
  parser.moveCurrent();
}

void SumExpr::execute(Forth& forth, std::vector<Token>& tokens) {
  Parser& parser = Parser::getInstance(tokens, forth);
  int right = forth.pop();
  int left = forth.pop();
  int result;
  result = right + left;
  forth.push(result);
}

void MultExpr::execute(Forth &forth, std::vector<Token>& tokens) {
  int right = forth.pop();
  int left = forth.pop();
  int result;
  result = left * right;

  forth.push(result);
}

void SubsExpr::execute(Forth &forth, std::vector<Token>& tokens) {
  int right = forth.pop();
  int left = forth.pop();
  int result;
  result = left - right;

  forth.push(result);
}

void ModExpr::execute(Forth &forth, std::vector<Token>& tokens) {
  int right = forth.pop();
  int left = forth.pop();
  if (right == 0) {
    throw std::runtime_error("Div by zero!");
  }

  int result = left % right;
  forth.push(result);
}

void SlashExpr::execute(Forth &forth, std::vector<Token>& tokens) {
  int right = forth.pop();
  int left = forth.pop();
  if (right == 0) {
    throw std::runtime_error("Div by zero!");
  }
  int result = left / right;
  forth.push(result);
}

void EmitExpr::execute(Forth &forth, std::vector<Token>& tokens) {
  int popped = forth.pop();
  std::cout << static_cast<char>(popped);
}

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

//DUMPSTER


// //+ - / * mod
// void Arithmetical::execute(Forth &forth) {
//   int rightValue = forth.pop();
//   int leftValue = forth.pop();
//   int result;

//   switch (operatorToken) {
//   case TokenType::PLUS:
//     result = leftValue + rightValue;
//     break;
//   case TokenType::MINUS:
//     result = leftValue - rightValue;
//     break;
//   case TokenType::STAR:
//     result = leftValue * rightValue;
//     break;
//   case TokenType::SLASH:
//     if (rightValue == 0) {
//       throw std::runtime_error("Division by zero");
//     }
//     result = leftValue / rightValue;
//     break;
//   case TokenType::MOD:
//     if (rightValue == 0) {
//       throw std::runtime_error("Modulo by zero");
//     }
//     result = leftValue % rightValue;
//     break;
//   default:
//     throw std::runtime_error("Unknown operator");
//   }
