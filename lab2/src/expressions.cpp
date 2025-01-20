#include "expressions.hpp"
#include "ExecutionContext.hpp"
#include "Token.hpp"
#include "UserInterface.hpp"
#include "interpreter.hpp"

#include <cstdlib>
#include <stdexcept>
#include <string>
#include <iostream>
#include <vector>

void handleIf (ExecutionContext* context, size_t& savedPosition);
void handleElse (ExecutionContext* context, size_t& savedPosition);
void handleThen (ExecutionContext* context);
int parseNumber(const std::string &lexeme);

//Numbersss
void PushNumberExpr::execute(ExecutionContext* context) { 
  const int value = parseNumber(context->getTokenManager().getTokens()[context->getTokenManager().getCurrent() - 1].getLexeme());
  context->getStackManager().push(value); 
}

void DupExpr::execute(ExecutionContext* context) {
  const int topValue = context->getStackManager().peek();
  context->getStackManager().push(topValue);
}

void CrExpr::execute(ExecutionContext* context) {
  context->getBufferManager().addToBuffer("\n");
}

void DotExpr::execute(ExecutionContext* context) {
  const int popped = context->getStackManager().peek();
  context->getBufferManager().addToBuffer(std::to_string(popped));
}

void SwapExpr::execute(ExecutionContext* context) {
  const int val1 = context->getStackManager().pop();
  const int val2 = context->getStackManager().pop();
  context->getStackManager().push(val1);
  context->getStackManager().push(val2);

}

void IExpr::execute(ExecutionContext* context) {
  int iterator = context->getTokenManager().getIterator();
  context->getStackManager().push(iterator);
}

void DropExpr::execute(ExecutionContext* context) {context->getStackManager().pop(); }

//."
void PrintStrExpr::execute(ExecutionContext *context) {
  Token curToken = context->getTokenManager().getCurrentToken();

  if (curToken.getLexeme() == "\"") {
    UserInterface::displayMessage("");
    context->getTokenManager().moveCurrent();
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

    context->getTokenManager().moveCurrent();
    curToken = context->getTokenManager().getCurrentToken();
    // curToken = tokens[context.getTokenManager().getCurrent()];
  }

  if (curToken.getType() == TokenType::END) {
    throw std::runtime_error("NO STRING AFTER .\"!!!");
  }

  context->getBufferManager().addToBuffer(str);

  if (curToken.getType() == TokenType::QUOTS ||
      curToken.getType() == TokenType::DQUOTS) {
    context->getTokenManager().moveCurrent();
    return;
  }
}

void RotExpr::execute(ExecutionContext* context){
  ExecutionContext::StackManager& stack = context->getStackManager();
  const int a = stack.pop();
  const int b = stack.pop();
  const int c = stack.pop();

  stack.push(a);
  stack.push(c);
  stack.push(b);
}

void OverExpr::execute(ExecutionContext* context){
  ExecutionContext::StackManager& stack = context->getStackManager();
  const int top = stack.pop();
  const int second = stack.pop();

  stack.push(second);
  stack.push(top);
  stack.push(second);
}

void CycleExpr::execute(ExecutionContext* context) {
  // Interpreter &context.getTokenManager() = Interpreter::getInstance(tokens, context.getStackManager());
  ExecutionContext::StackManager& stack = context->getStackManager();
  ExecutionContext::TokenManager& tokens = context->getTokenManager();
  Interpreter interpretator(context);

  // int passable_semicolons = 0;
  const int begin = stack.pop();
  const int end = stack.pop();
  const int inc = begin > end ? -1 : 1;

  size_t start_index = tokens.getCurrent();
  size_t loop_size = 0;

  while (tokens.getCurrentToken().getLexeme() != "loop") {
    if (tokens.getCurrentToken().getType() == TokenType::END) {
      throw std::runtime_error("No loop after do!\n");
    }
    loop_size++;
    tokens.moveCurrent();
  }
  tokens.placeCurrent(start_index);

  for (int loop_iterator = begin; loop_iterator != end; loop_iterator += inc) {
    tokens.setLoopIterator(loop_iterator);
    for (; tokens.getCurrent() - start_index < loop_size;) {
      interpretator.executeExpr();
    }
    tokens.placeCurrent(start_index);
  }
  tokens.placeCurrent(start_index + loop_size); //after loop
  // tokens.dropToken(tokens.getCurrent()); //SUS
  handleThen(context);
}

void SumExpr::execute(ExecutionContext* context) {
  const int right = context->getStackManager().pop();
  const int left = context->getStackManager().pop();
  const int result = right + left;
  context->getStackManager().push(result);
}

void MultExpr::execute(ExecutionContext* context) {
  const int right = context->getStackManager().pop();
  const int left = context->getStackManager().pop();
  const int result = left * right;

  context->getStackManager().push(result);
}

void SubsExpr::execute(ExecutionContext* context) {
  const int right = context->getStackManager().pop();
  const int left = context->getStackManager().pop();
  const int result = left - right;

  context->getStackManager().push(result);
}

void ModExpr::execute(ExecutionContext* context) {
  const int right = context->getStackManager().pop();
  const int left = context->getStackManager().pop();
  if (right == 0) {
    throw std::runtime_error("Div by zero!");
  }
  const int result = left % right;
  context->getStackManager().push(result);
}

void SlashExpr::execute(ExecutionContext* context) {
  const int right = context->getStackManager().pop();
  const int left = context->getStackManager().pop();
  if (right == 0) {
    throw std::runtime_error("Div by zero!");
  }
  const int result = left / right;
  context->getStackManager().push(result);
}


void EmitExpr::execute(ExecutionContext* context) {
  const int popped = context->getStackManager().pop();
   std::string message(1, static_cast<char>(popped)); 
  context->getBufferManager().addToBuffer(message);
}

void ConditionalExpr::execute(ExecutionContext* context) {
  size_t savedPosition = context->getTokenManager().getCurrent();

  if (context->getStackManager().pop()) {
    handleIf(context, savedPosition);
  } else {
    handleElse(context, savedPosition);
  }
  handleThen(context);
  context->getTokenManager().placeCurrent(savedPosition);
}


// just ignore all the tokens that after then
void handleThen(ExecutionContext *context) {
  while (context->getTokenManager().getCurrentToken().getType() != TokenType::SEMICOLON) {
    if (context->getTokenManager().getCurrentToken().getType() == TokenType::END) {
      throw std::runtime_error("No semicolon!");
    }
    // tokens.dropToken(tokens.getCurrent());
  context->getTokenManager().moveCurrent();
  }
}

// execute only those commands that come before else or then
void handleIf(ExecutionContext* context, size_t& savedPosition) {
  Interpreter interpretator(context); 

  while (context->getTokenManager().getCurrentToken().getLexeme() != "else" &&
         context->getTokenManager().getCurrentToken().getLexeme() != "then" &&
         context->getTokenManager().getCurrentToken().getType() != TokenType::END) {
    interpretator.executeExpr();
  }
  // skip the semicolon
  if (context->getTokenManager().getCurrentToken().getType() == TokenType::SEMICOLON) {
    context->getTokenManager().moveCurrent();
    return;
  }

  // skip
  while (context->getTokenManager().getCurrentToken().getType() != TokenType::SEMICOLON &&
         context->getTokenManager().getCurrentToken().getType() != TokenType::END) {
    context->getTokenManager().moveCurrent();
    savedPosition = context->getTokenManager().getCurrent();
  }
}

// execute only those commands that come after else
void handleElse(ExecutionContext* context, size_t& savedPosition) {
  Interpreter interpretator(context); 
  // find else or then
  while (context->getTokenManager().getCurrentToken().getLexeme() != "then" &&
         context->getTokenManager().getCurrentToken().getLexeme() != "else" &&
         context->getTokenManager().getCurrentToken().getType() != TokenType::END) {
    context->getTokenManager().moveCurrent();
  }

  // ends execution (will ignore else after then)
  if (context->getTokenManager().getCurrentToken().getLexeme() == "then") {
    handleThen(context);
    return;
  }

  // skip else
  context->getTokenManager().moveCurrent();
  // savedPosition = context.getTokenManager().getCurrent();

  while (context->getTokenManager().getCurrentToken().getType() != TokenType::SEMICOLON &&
         context->getTokenManager().getCurrentToken().getLexeme() != "then" &&
         context->getTokenManager().getCurrentToken().getType() != TokenType::END) {
    interpretator.executeExpr();
  }
  savedPosition = context->getTokenManager().getCurrent();

  if (context->getTokenManager().getCurrentToken().getLexeme() == "then") {
    handleThen(context);
  }
}


void EqualExpr::execute(ExecutionContext* context){
  const int val1 = context->getStackManager().pop();
  const int val2 = context->getStackManager().pop();

  context->getStackManager().push(val1 == val2);
}

void LessExpr::execute(ExecutionContext* context){
  const int val1 = context->getStackManager().pop();
  const int val2 = context->getStackManager().pop();

  context->getStackManager().push(val2 < val1);
}

void GreaterExpr::execute(ExecutionContext* context){
  const int val1 = context->getStackManager().pop();
  const int val2 = context->getStackManager().pop();

  context->getStackManager().push(val2 > val1);
}

// void LogicExpr::execute(ExecutionContext* context) {
//   Interpreter &context.getTokenManager() = Interpreter::getInstance(tokens, context.getStackManager());
//   Token curToken = context.getTokenManager().getPrevious();
  
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



//=========DUMPSTER


// void ConditionalExpr::execute(ExecutionContext& context) {
//   Interpreter &context.getTokenManager() = Interpreter::getInstance(tokens, context.getStackManager());
//   size_t savedPosition = context.getTokenManager().getCurrent();

//   if (context.getStackManager().pop()) {
//     std::cout << "Doing if!" << std::endl;
//     while (context.getTokenManager().getCurrentToken().getLexeme() != "else" && context.getTokenManager().getCurrentToken().getLexeme() != "then" &&
//            context.getTokenManager().getCurrentToken().getType() != TokenType::END) {
//       context.getTokenManager().moveCurrent();
//     }
//     context.getTokenManager().dropToken(context.getTokenManager().getCurrent());
//     while (context.getTokenManager().getCurrentToken().getType() != TokenType::SEMICOLON &&
//            context.getTokenManager().getCurrentToken().getType() != TokenType::END) {
//       context.getTokenManager().dropToken(context.getTokenManager().getCurrent());
//     }
//   } else {
//     std::cout << "Doing else!" << std::endl;
//     while (context.getTokenManager().getCurrentToken().getLexeme() != "then" &&
//            context.getTokenManager().getCurrentToken().getType() != TokenType::END) {
//             std::cout << "Current is " << context.getTokenManager().getCurrentToken().getLexeme() << std::endl;
//             context.getTokenManager().dropToken(context.getTokenManager().getCurrent());  
//     }
//     context.getTokenManager().dropToken(context.getTokenManager().getCurrent());
//     savedPosition = context.getTokenManager().getCurrent();
//     while (context.getTokenManager().getCurrentToken().getType() != TokenType::SEMICOLON &&
//            context.getTokenManager().getCurrentToken().getType() != TokenType::END) {
//       context.getTokenManager().moveCurrent();
//     }
//   }
//   context.getTokenManager().dropToken(context.getTokenManager().getCurrent());
//   context.getTokenManager().placeCurrent(savedPosition);
//   std::cout << "Current is " << tokens[context.getTokenManager().getCurrent()].getLexeme() << std::endl;
// }

// void ConditionalExpr::execute(ExecutionContext& context) {
//     Interpreter &context.getTokenManager() = Interpreter::getInstance(tokens, context.getStackManager());
//     size_t savedPosition = context.getTokenManager().getCurrent();

//     if (context.getStackManager().pop()) {
//         std::cout << "Doing if!" << std::endl;
//         executeBranch(context.getStackManager(), context.getTokenManager().getTokens());
//     } else {
//         std::cout << "Doing else or then!" << std::endl;
//         executeElseBranch(context.getTokenManager().getTokens(), context.getStackManager());
//     }

//     context.getTokenManager().dropToken(context.getTokenManager().getCurrent());
//     context.getTokenManager().placeCurrent(savedPosition);
//     std::cout << "Current is " << tokens[context.getTokenManager().getCurrent()].getLexeme() << std::endl;
// }

// void ConditionalExpr::executeBranch(Forth &context.getStackManager(), ExecutionContext& context) {
//     Interpreter &context.getTokenManager() = Interpreter::getInstance(tokens, context.getStackManager());

//     while (context.getTokenManager().getCurrentToken().getType() != TokenType::END &&
//            context.getTokenManager().getCurrentToken().getLexeme() != "then" &&
//            context.getTokenManager().getCurrentToken().getType() != TokenType::END) {
//         context.getTokenManager().executeExpr();
//     }

//     // Drop the semicolon if present
//     if (context.getTokenManager().getCurrentToken().getType() == TokenType::SEMICOLON) {
//         context.getTokenManager().dropToken(context.getTokenManager().getCurrent());
//     }

//     // Skip to the end of the branch
//     while (context.getTokenManager().getCurrentToken().getType() != TokenType::SEMICOLON &&
//            context.getTokenManager().getCurrentToken().getType() != TokenType::END) {
//         context.getTokenManager().dropToken(context.getTokenManager().getCurrent());
//     }
// }

// void ConditionalExpr::executeElseBranch(ExecutionContext& context, Forth &context.getStackManager()) {
//     Interpreter &context.getTokenManager() = Interpreter::getInstance(tokens, context.getStackManager());

//     while (context.getTokenManager().getCurrentToken().getLexeme() != "then" &&
//            context.getTokenManager().getCurrentToken().getLexeme() != "else" &&
//            context.getTokenManager().getCurrentToken().getType() != TokenType::END) {
//         context.getTokenManager().dropToken(context.getTokenManager().getCurrent());
//     }

//     if (context.getTokenManager().getCurrentToken().getLexeme() == "then") {
//         handleThen(context.getTokenManager().getTokens(), context.getStackManager());
//         return;
//     }

//     // Remove the "else" token
//     if (context.getTokenManager().getCurrentToken().getLexeme() == "else") {
//         context.getTokenManager().dropToken(context.getTokenManager().getCurrent());
//     }

//     // Execute the ELSE_BRANCH
//     executeBranch(context.getStackManager(), context.getTokenManager().getTokens());
// }

// void ConditionalExpr::handleThen(ExecutionContext& context, Forth &context.getStackManager()) {
//   Interpreter &context.getTokenManager() = Interpreter::getInstance(tokens, context.getStackManager());
//     while (context.getTokenManager().getCurrentToken().getType() != TokenType::SEMICOLON) {
//         if (context.getTokenManager().getCurrentToken().getType() == TokenType::END) {
//             throw std::runtime_error("No semicolon after if!");
//         }
//         context.getTokenManager().dropToken(context.getTokenManager().getCurrent());
//     }
// }



// //+ - / * mod
// void Arithmetical::execute(Forth &context.getStackManager()) {
//   int rightValue = context.getStackManager().pop();
//   int leftValue = context.getStackManager().pop();
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
