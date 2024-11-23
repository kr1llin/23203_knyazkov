#include "expressions.hpp"

void PushNumberExpr::execute(Forth &forth) { forth.push(value); }

void DupExpr::execute(Forth &forth) {
  int topValue = forth.peek();
  forth.push(topValue);
}

void DropExpr::execute(Forth &forth) { forth.pop(); }

//+ - / * mod
void Arithmetical::execute(Forth &forth) {
  // Execute left and right expressions
  left->execute(forth);
  right->execute(forth);

  int rightValue = forth.pop();
  int leftValue = forth.pop();
  int result;

  switch (operatorToken) {
  case TokenType::PLUS:
    result = leftValue + rightValue;
    break;
  case TokenType::MINUS:
    result = leftValue - rightValue;
    break;
  case TokenType::STAR:
    result = leftValue * rightValue;
    break;
  case TokenType::SLASH:
    if (rightValue == 0) {
      throw std::runtime_error("Division by zero");
    }
    result = leftValue / rightValue;
    break;
  case TokenType::MOD:
    if (rightValue == 0) {
      throw std::runtime_error("Modulo by zero");
    }
    result = leftValue % rightValue;
    break;
  default:
    throw std::runtime_error("Unknown operator");
  }

  forth.push(result);
}

void SumExpr::execute(Forth &forth) {
  // Execute left and right expressions
  right = forth.pop();
  left = forth.pop();
  int result;
  result = right + left;

  forth.push(result);
}
