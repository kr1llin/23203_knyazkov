#include "expressions.hpp"
#include "UserInterface.hpp"
#include "Token.hpp"
#include "parser.hpp"

#include <cstdlib>
#include <stdexcept>
#include <string>
#include <vector>

void handleIf (Parser& parser, size_t& savedPosition);
void handleElse (Parser& parser, size_t& savedPosition);
void handleThen (Parser& parser);

int parseNumber(const std::string &lexeme);

void DupExpr::execute(Forth &forth, std::vector<Token>& tokens) {
  int topValue = forth.peek();
  forth.push(topValue);
}

void CrExpr::execute(Forth &forth, std::vector<Token>& tokens) {
  UserInterface::getInstance().displayMessage("\n");
}

void IExpr::execute(Forth &forth, std::vector<Token>& tokens) {
  UserInterface::getInstance().displayMessage(std::to_string(forth.loop_i));
}

void DropExpr::execute(Forth &forth, std::vector<Token>& tokens) {forth.pop(); }

//Numbersss
void PushNumberExpr::execute(Forth &forth, std::vector<Token>& tokens) { 
  Parser& parser = Parser::getInstance(tokens, forth);
  int value = parseNumber(tokens[tokenNumber].getLexeme());
  forth.push(value); 
}

//."
// make it handle ." ."
void PrintStrExpr::execute(Forth &forth, std::vector<Token> &tokens) {
  Parser &parser = Parser::getInstance(tokens, forth);
  Token curToken = tokens[parser.getCurrent()];

  if (curToken.getLexeme() == "\"") {
    UserInterface::getInstance().displayMessage("");
    parser.moveCurrent();
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

    parser.moveCurrent();
    curToken = tokens[parser.getCurrent()];
  }

  if (curToken.getType() == TokenType::END) {
    throw std::runtime_error("NO STRING AFTER .\"!!!");
  }
  UserInterface::getInstance().displayMessage(str);

  if (curToken.getType() == TokenType::QUOTS ||
      curToken.getType() == TokenType::DQUOTS) {
    parser.moveCurrent();
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
  Parser &parser = Parser::getInstance(tokens, forth);
  int begin = forth.pop();
  int end = forth.pop();
  int inc = begin > end ? -1 : 1;

  size_t start_index = parser.getCurrent();

  std::vector<std::unique_ptr<Expr>> loop_body{};
  int &i = forth.loop_i;

  for (i = begin; i != end; i += inc) {

    while (parser.getCurrentToken().getLexeme() != "loop" &&
           parser.getCurrentToken().getType() != TokenType::END &&
           parser.getCurrentToken().getType() != TokenType::SEMICOLON) {
      parser.executeExpr();
    }
    parser.placeCurrent(start_index);
  }
  parser.placeCurrent(start_index + loop_body.size());
  parser.dropToken(parser.getCurrent());
  handleThen(parser);
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

void ConditionalExpr::execute(Forth &forth, std::vector<Token> &tokens) {
  Parser &parser = Parser::getInstance(tokens, forth);
  size_t savedPosition = parser.getCurrent();

  if (forth.pop()) {
    handleIf(parser, savedPosition);
  } else {
    handleElse(parser, savedPosition);
  }
  parser.dropToken(parser.getCurrent());
  parser.placeCurrent(savedPosition);
}

void EmitExpr::execute(Forth &forth, std::vector<Token>& tokens) {
  int popped = forth.pop();
   std::string message(1, static_cast<char>(popped)); 
  UserInterface::getInstance().displayMessage(message);
}

//just ignore all the tokens that after then
void handleThen(Parser& parser){
  while (parser.getCurrentToken().getType() != TokenType::SEMICOLON) {
    if (parser.getCurrentToken().getType() == TokenType::END) {
      throw std::runtime_error("No semicolon!");
    }
    parser.dropToken(parser.getCurrent());
  }
  return;
}

//execute only those commands that come before else or then
void handleIf (Parser& parser, size_t& savedPosition){
   while (parser.getCurrentToken().getLexeme() != "else" && parser.getCurrentToken().getLexeme() != "then" &&
           parser.getCurrentToken().getType() != TokenType::END) {
            parser.executeExpr();
    }
    //drop the semicolon
    if (parser.getCurrentToken().getType() == TokenType::SEMICOLON){
      parser.dropToken(parser.getCurrent());
    }

    //skip 
    while (parser.getCurrentToken().getType() != TokenType::SEMICOLON &&
           parser.getCurrentToken().getType() != TokenType::END) {
      parser.dropToken(parser.getCurrent());
    savedPosition = parser.getCurrent();
    }
}

//execute only those commands that come after else
void handleElse (Parser& parser, size_t& savedPosition){
  // find else or then
  while (parser.getCurrentToken().getLexeme() != "then" &&
         parser.getCurrentToken().getLexeme() != "else" &&
         parser.getCurrentToken().getType() != TokenType::END) {
    parser.dropToken(parser.getCurrent()); // we don't need that
  }

  //ends execution (it will ignore else after then)
  if (parser.getCurrentToken().getLexeme() == "then") {
        handleThen(parser);
  }

  // remove else
  parser.dropToken(parser.getCurrent());
  // savedPosition = parser.getCurrent();

  while (parser.getCurrentToken().getType() != TokenType::SEMICOLON &&
         parser.getCurrentToken().getLexeme() != "then" &&
         parser.getCurrentToken().getType() != TokenType::END) {
    parser.executeExpr();
  }
  savedPosition = parser.getCurrent();

  if (parser.getCurrentToken().getLexeme() == "then") {
    handleThen(parser);
  }
}


// void ConditionalExpr::execute(Forth &forth, std::vector<Token> &tokens) {
//   Parser &parser = Parser::getInstance(tokens, forth);
//   size_t savedPosition = parser.getCurrent();

//   if (forth.pop()) {
//     std::cout << "Doing if!" << std::endl;
//     while (parser.getCurrentToken().getLexeme() != "else" && parser.getCurrentToken().getLexeme() != "then" &&
//            parser.getCurrentToken().getType() != TokenType::END) {
//       parser.moveCurrent();
//     }
//     parser.dropToken(parser.getCurrent());
//     while (parser.getCurrentToken().getType() != TokenType::SEMICOLON &&
//            parser.getCurrentToken().getType() != TokenType::END) {
//       parser.dropToken(parser.getCurrent());
//     }
//   } else {
//     std::cout << "Doing else!" << std::endl;
//     while (parser.getCurrentToken().getLexeme() != "then" &&
//            parser.getCurrentToken().getType() != TokenType::END) {
//             std::cout << "Current is " << parser.getCurrentToken().getLexeme() << std::endl;
//             parser.dropToken(parser.getCurrent());  
//     }
//     parser.dropToken(parser.getCurrent());
//     savedPosition = parser.getCurrent();
//     while (parser.getCurrentToken().getType() != TokenType::SEMICOLON &&
//            parser.getCurrentToken().getType() != TokenType::END) {
//       parser.moveCurrent();
//     }
//   }
//   parser.dropToken(parser.getCurrent());
//   parser.placeCurrent(savedPosition);
//   std::cout << "Current is " << tokens[parser.getCurrent()].getLexeme() << std::endl;
// }

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
//   Parser &parser = Parser::getInstance(tokens, forth);
//   Token curToken = parser.getPrevious();
  
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
//     Parser &parser = Parser::getInstance(tokens, forth);
//     size_t savedPosition = parser.getCurrent();

//     if (forth.pop()) {
//         std::cout << "Doing if!" << std::endl;
//         executeBranch(forth, parser.getTokens());
//     } else {
//         std::cout << "Doing else or then!" << std::endl;
//         executeElseBranch(parser.getTokens(), forth);
//     }

//     parser.dropToken(parser.getCurrent());
//     parser.placeCurrent(savedPosition);
//     std::cout << "Current is " << tokens[parser.getCurrent()].getLexeme() << std::endl;
// }

// void ConditionalExpr::executeBranch(Forth &forth, std::vector<Token> &tokens) {
//     Parser &parser = Parser::getInstance(tokens, forth);

//     while (parser.getCurrentToken().getType() != TokenType::END &&
//            parser.getCurrentToken().getLexeme() != "then" &&
//            parser.getCurrentToken().getType() != TokenType::END) {
//         parser.executeExpr();
//     }

//     // Drop the semicolon if present
//     if (parser.getCurrentToken().getType() == TokenType::SEMICOLON) {
//         parser.dropToken(parser.getCurrent());
//     }

//     // Skip to the end of the branch
//     while (parser.getCurrentToken().getType() != TokenType::SEMICOLON &&
//            parser.getCurrentToken().getType() != TokenType::END) {
//         parser.dropToken(parser.getCurrent());
//     }
// }

// void ConditionalExpr::executeElseBranch(std::vector<Token> &tokens, Forth &forth) {
//     Parser &parser = Parser::getInstance(tokens, forth);

//     while (parser.getCurrentToken().getLexeme() != "then" &&
//            parser.getCurrentToken().getLexeme() != "else" &&
//            parser.getCurrentToken().getType() != TokenType::END) {
//         parser.dropToken(parser.getCurrent());
//     }

//     if (parser.getCurrentToken().getLexeme() == "then") {
//         handleThen(parser.getTokens(), forth);
//         return;
//     }

//     // Remove the "else" token
//     if (parser.getCurrentToken().getLexeme() == "else") {
//         parser.dropToken(parser.getCurrent());
//     }

//     // Execute the ELSE_BRANCH
//     executeBranch(forth, parser.getTokens());
// }

// void ConditionalExpr::handleThen(std::vector<Token> &tokens, Forth &forth) {
//   Parser &parser = Parser::getInstance(tokens, forth);
//     while (parser.getCurrentToken().getType() != TokenType::SEMICOLON) {
//         if (parser.getCurrentToken().getType() == TokenType::END) {
//             throw std::runtime_error("No semicolon after if!");
//         }
//         parser.dropToken(parser.getCurrent());
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
