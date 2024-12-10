#include "expressions.hpp"
#include "UserInterface.hpp"
#include "Token.hpp"
#include "interpreter.hpp"

#include <cstdlib>
#include <stdexcept>
#include <string>
#include <iostream>
#include <vector>

void handleIf (Interpreter& interpreter, size_t& savedPosition);
void handleElse (Interpreter& interpreter, size_t& savedPosition);
void handleThen (Interpreter& interpreter);

int parseNumber(const std::string &lexeme);

void DupExpr::execute(Forth &forth, std::vector<Token>& tokens) {
  int topValue = forth.peek();
  forth.push(topValue);
}

void CrExpr::execute(Forth &forth, std::vector<Token>& tokens) {
  forth.addToBuffer("\n");
}

void DotExpr::execute(Forth &forth, std::vector<Token>& tokens) {
  int popped = forth.pop();
  forth.addToBuffer(std::to_string(popped));
}

void IExpr::execute(Forth &forth, std::vector<Token>& tokens) {
  forth.addToBuffer(std::to_string(forth.getIterator()));
}

void DropExpr::execute(Forth &forth, std::vector<Token>& tokens) {forth.pop(); }

//Numbersss
void PushNumberExpr::execute(Forth &forth, std::vector<Token>& tokens) { 
  Interpreter& interpreter = Interpreter::getInstance(tokens, forth);
  int value = parseNumber(tokens[tokenNumber].getLexeme());
  forth.push(value); 
}

//."
void PrintStrExpr::execute(Forth &forth, std::vector<Token> &tokens) {
  Interpreter &interpreter = Interpreter::getInstance(tokens, forth);
  Token curToken = tokens[interpreter.getCurrent()];

  if (curToken.getLexeme() == "\"") {
    UserInterface::getInstance().displayMessage("");
    interpreter.moveCurrent();
    return;
  }

  string str{};

  while (curToken.getType() != TokenType::END &&
         curToken.getType() != TokenType::QUOTS) {
    if (curToken.getType() == TokenType::DQUOTS) {
      str += ".";
      break;
    }
    str += (curToken.getType() == TokenType::STRING) ? curToken.getLiteral()
                                                     : curToken.getLexeme();

    interpreter.moveCurrent();
    curToken = tokens[interpreter.getCurrent()];
  }

  if (curToken.getType() == TokenType::END) {
    throw std::runtime_error("NO STRING AFTER .\"!!!");
  }

  forth.addToBuffer(str);

  if (curToken.getType() == TokenType::QUOTS ||
      curToken.getType() == TokenType::DQUOTS) {
    interpreter.moveCurrent();
    return;
  }
}

void RotExpr::execute(Forth& forth, std::vector<Token>& tokens){
  int a = forth.pop();
  int b = forth.pop();
  int c = forth.pop();

  forth.push(a);
  forth.push(c);
  forth.push(b);
}

void OverExpr::execute(Forth& forth, std::vector<Token>& tokens){
  int top = forth.pop();
  int second = forth.pop();

  forth.push(second);
  forth.push(top);
  forth.push(second);
}

void CycleExpr::execute(Forth &forth, std::vector<Token> &tokens) {
  Interpreter &interpreter = Interpreter::getInstance(tokens, forth);
  int begin = forth.pop();
  int end = forth.pop();
  int inc = begin > end ? -1 : 1;

  size_t start_index = interpreter.getCurrent();

  std::vector<std::unique_ptr<Expr>> loop_body{};
  int &i = forth.getIterator();

  for (i = begin; i != end; i += inc) {
    while (interpreter.getCurrentToken().getLexeme() != "loop" &&
           interpreter.getCurrentToken().getType() != TokenType::END &&
           interpreter.getCurrentToken().getType() != TokenType::SEMICOLON) {
      interpreter.executeExpr();
    }
    interpreter.placeCurrent(start_index);
  }
  interpreter.placeCurrent(start_index + loop_body.size());
  interpreter.dropToken(interpreter.getCurrent());
  handleThen(interpreter);
}

void SumExpr::execute(Forth& forth, std::vector<Token>& tokens) {
  Interpreter& interpreter = Interpreter::getInstance(tokens, forth);
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

void SubsExpr::execute(Forth &forth, std::vector<Token> &tokens) {
  int right = forth.pop();
  int left = forth.pop();
  int result;
  result = left - right;

  forth.push(result);
}

void ModExpr::execute(Forth &forth, std::vector<Token> &tokens) {
  int right = forth.pop();
  int left = forth.pop();
  if (right == 0) {
    throw std::runtime_error("Div by zero!");
  }
  int result = left % right;
  forth.push(result);
}

void SlashExpr::execute(Forth &forth, std::vector<Token> &tokens) {
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
   std::string message(1, static_cast<char>(popped)); 
  forth.addToBuffer(message);
}

void ConditionalExpr::execute(Forth &forth, std::vector<Token> &tokens) {
  Interpreter &interpreter = Interpreter::getInstance(tokens, forth);
  size_t savedPosition = interpreter.getCurrent();

  if (forth.pop()) {
    handleIf(interpreter, savedPosition);
  } else {
    handleElse(interpreter, savedPosition);
  }
  interpreter.dropToken(interpreter.getCurrent());
  interpreter.placeCurrent(savedPosition);
}


// just ignore all the tokens that after then
void handleThen(Interpreter &interpreter) {
  while (interpreter.getCurrentToken().getType() != TokenType::SEMICOLON) {
    if (interpreter.getCurrentToken().getType() == TokenType::END) {
      throw std::runtime_error("No semicolon!");
    }
    interpreter.dropToken(interpreter.getCurrent());
  }
  return;
}

// execute only those commands that come before else or then
void handleIf(Interpreter &interpreter, size_t &savedPosition) {
  while (interpreter.getCurrentToken().getLexeme() != "else" &&
         interpreter.getCurrentToken().getLexeme() != "then" &&
         interpreter.getCurrentToken().getType() != TokenType::END) {
    interpreter.executeExpr();
  }
  // drop the semicolon
  if (interpreter.getCurrentToken().getType() == TokenType::SEMICOLON) {
    interpreter.dropToken(interpreter.getCurrent());
    return;
  }

  // skip
  while (interpreter.getCurrentToken().getType() != TokenType::SEMICOLON &&
         interpreter.getCurrentToken().getType() != TokenType::END) {
    interpreter.dropToken(interpreter.getCurrent());
    savedPosition = interpreter.getCurrent();
  }
}

// execute only those commands that come after else
void handleElse(Interpreter &interpreter, size_t &savedPosition) {
  // find else or then
  while (interpreter.getCurrentToken().getLexeme() != "then" &&
         interpreter.getCurrentToken().getLexeme() != "else" &&
         interpreter.getCurrentToken().getType() != TokenType::END) {
    interpreter.dropToken(interpreter.getCurrent()); // we don't need that
  }

  // ends execution (it will ignore else after then)
  if (interpreter.getCurrentToken().getLexeme() == "then") {
    handleThen(interpreter);
    return;
  }

  // remove else
  interpreter.dropToken(interpreter.getCurrent());
  // savedPosition = interpreter.getCurrent();

  while (interpreter.getCurrentToken().getType() != TokenType::SEMICOLON &&
         interpreter.getCurrentToken().getLexeme() != "then" &&
         interpreter.getCurrentToken().getType() != TokenType::END) {
    interpreter.executeExpr();
  }
  savedPosition = interpreter.getCurrent();

  if (interpreter.getCurrentToken().getLexeme() == "then") {
    handleThen(interpreter);
  }
}


void EqualExpr::execute(Forth &forth, std::vector<Token>& tokens){
  int val1 = forth.pop();
  int val2 = forth.pop();

  forth.push(val1 == val2);
}

void LessExpr::execute(Forth &forth, std::vector<Token>& tokens){
  int val1 = forth.pop();
  int val2 = forth.pop();

  forth.push(val1 < val2);
}

void GreaterExpr::execute(Forth &forth, std::vector<Token>& tokens){
  int val1 = forth.pop();
  int val2 = forth.pop();

  forth.push(val1 > val2);
}

// void LogicExpr::execute(Forth &forth, std::vector<Token> &tokens) {
//   Interpreter &interpreter = Interpreter::getInstance(tokens, forth);
//   Token curToken = interpreter.getPrevious();
  
// }

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


// void ConditionalExpr::execute(Forth &forth, std::vector<Token> &tokens) {
//   Interpreter &interpreter = Interpreter::getInstance(tokens, forth);
//   size_t savedPosition = interpreter.getCurrent();

//   if (forth.pop()) {
//     std::cout << "Doing if!" << std::endl;
//     while (interpreter.getCurrentToken().getLexeme() != "else" && interpreter.getCurrentToken().getLexeme() != "then" &&
//            interpreter.getCurrentToken().getType() != TokenType::END) {
//       interpreter.moveCurrent();
//     }
//     interpreter.dropToken(interpreter.getCurrent());
//     while (interpreter.getCurrentToken().getType() != TokenType::SEMICOLON &&
//            interpreter.getCurrentToken().getType() != TokenType::END) {
//       interpreter.dropToken(interpreter.getCurrent());
//     }
//   } else {
//     std::cout << "Doing else!" << std::endl;
//     while (interpreter.getCurrentToken().getLexeme() != "then" &&
//            interpreter.getCurrentToken().getType() != TokenType::END) {
//             std::cout << "Current is " << interpreter.getCurrentToken().getLexeme() << std::endl;
//             interpreter.dropToken(interpreter.getCurrent());  
//     }
//     interpreter.dropToken(interpreter.getCurrent());
//     savedPosition = interpreter.getCurrent();
//     while (interpreter.getCurrentToken().getType() != TokenType::SEMICOLON &&
//            interpreter.getCurrentToken().getType() != TokenType::END) {
//       interpreter.moveCurrent();
//     }
//   }
//   interpreter.dropToken(interpreter.getCurrent());
//   interpreter.placeCurrent(savedPosition);
//   std::cout << "Current is " << tokens[interpreter.getCurrent()].getLexeme() << std::endl;
// }

// void ConditionalExpr::execute(Forth &forth, std::vector<Token> &tokens) {
//     Interpreter &interpreter = Interpreter::getInstance(tokens, forth);
//     size_t savedPosition = interpreter.getCurrent();

//     if (forth.pop()) {
//         std::cout << "Doing if!" << std::endl;
//         executeBranch(forth, interpreter.getTokens());
//     } else {
//         std::cout << "Doing else or then!" << std::endl;
//         executeElseBranch(interpreter.getTokens(), forth);
//     }

//     interpreter.dropToken(interpreter.getCurrent());
//     interpreter.placeCurrent(savedPosition);
//     std::cout << "Current is " << tokens[interpreter.getCurrent()].getLexeme() << std::endl;
// }

// void ConditionalExpr::executeBranch(Forth &forth, std::vector<Token> &tokens) {
//     Interpreter &interpreter = Interpreter::getInstance(tokens, forth);

//     while (interpreter.getCurrentToken().getType() != TokenType::END &&
//            interpreter.getCurrentToken().getLexeme() != "then" &&
//            interpreter.getCurrentToken().getType() != TokenType::END) {
//         interpreter.executeExpr();
//     }

//     // Drop the semicolon if present
//     if (interpreter.getCurrentToken().getType() == TokenType::SEMICOLON) {
//         interpreter.dropToken(interpreter.getCurrent());
//     }

//     // Skip to the end of the branch
//     while (interpreter.getCurrentToken().getType() != TokenType::SEMICOLON &&
//            interpreter.getCurrentToken().getType() != TokenType::END) {
//         interpreter.dropToken(interpreter.getCurrent());
//     }
// }

// void ConditionalExpr::executeElseBranch(std::vector<Token> &tokens, Forth &forth) {
//     Interpreter &interpreter = Interpreter::getInstance(tokens, forth);

//     while (interpreter.getCurrentToken().getLexeme() != "then" &&
//            interpreter.getCurrentToken().getLexeme() != "else" &&
//            interpreter.getCurrentToken().getType() != TokenType::END) {
//         interpreter.dropToken(interpreter.getCurrent());
//     }

//     if (interpreter.getCurrentToken().getLexeme() == "then") {
//         handleThen(interpreter.getTokens(), forth);
//         return;
//     }

//     // Remove the "else" token
//     if (interpreter.getCurrentToken().getLexeme() == "else") {
//         interpreter.dropToken(interpreter.getCurrent());
//     }

//     // Execute the ELSE_BRANCH
//     executeBranch(forth, interpreter.getTokens());
// }

// void ConditionalExpr::handleThen(std::vector<Token> &tokens, Forth &forth) {
//   Interpreter &interpreter = Interpreter::getInstance(tokens, forth);
//     while (interpreter.getCurrentToken().getType() != TokenType::SEMICOLON) {
//         if (interpreter.getCurrentToken().getType() == TokenType::END) {
//             throw std::runtime_error("No semicolon after if!");
//         }
//         interpreter.dropToken(interpreter.getCurrent());
//     }
// }



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
