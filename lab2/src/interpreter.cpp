#include "ExecutionContext.hpp"
#include "interpreter.hpp"
#include "Token.hpp"
#include "expressions.hpp"
#include "factory.hpp"

#include <iostream>
#include <memory>
#include <ostream>

//*=======EXPRESSIONS========*//

void Interpreter::executeExpr() {
  auto expression = getExpression();
  if (expression) {
    expression->execute(context);
}
}

// get token - make expression - excecute
void Interpreter::interprete() {
  while (!context->getTokenManager().check(TokenType::END)) {
    executeExpr();
  }
}

std::unique_ptr<Expr> Interpreter::getExpression() {
  std::unique_ptr<Expr> expression;
  // std::cout << "Getting expression from " <<
  // context->getTokenManager().peekAtToken().getLexeme() << std::endl;
  Token curToken = context->getTokenManager().peekAtToken();
  if (isInIgnoreList(curToken)) {
    expression = std::unique_ptr<Expr>();
  } else if (context->getTokenManager().check(TokenType::NUMBER)) {
    expression = Factory<TokenType, Expr>::getInstance()->createCommandByName(
        TokenType::NUMBER);
  } else {
    expression = Factory<std::string, Expr>::getInstance()->createCommandByName(
        curToken.getLexeme());
  }
  context->getTokenManager().moveCurrent();
  return expression;
}

bool Interpreter::isInIgnoreList(Token& token) {
    const TokenType type = token.getType();
    const std::string lexeme = token.getLexeme();

    return ignoreTypeList.count(type) > 0 || ignoreLexemeList.count(lexeme);
}










// DUMPSTER

// for parse

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

// std::unique_ptr<Expr> Interpreter::expression() {
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
