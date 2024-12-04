#include "expressions.hpp"
#include "UserInterface.hpp"
#include "Token.hpp"
#include "parser.hpp"

#include <stdexcept>
#include <string>


int parseNumber(const std::string &lexeme);

void DupExpr::execute(Forth &forth, std::vector<Token>& tokens) {
  int topValue = forth.peek();
  forth.push(topValue);
}

void CrExpr::execute(Forth &forth, std::vector<Token>& tokens) {
  UserInterface::getInstance().displayMessage("\n");
}

void DropExpr::execute(Forth &forth, std::vector<Token>& tokens) {forth.pop(); }

//Numbersss
void PushNumberExpr::execute(Forth &forth, std::vector<Token>& tokens) { 
  Parser& parser = Parser::getInstance(tokens, forth);
  int value = parseNumber(tokens[tokenNumber].getLexeme());
  forth.push(value); 
}

//."
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
    str += (curToken.getType() == TokenType::STRING) ? curToken.getLiteral()
                                                     : curToken.getLexeme();
    str += " ";
    parser.moveCurrent();
    curToken = tokens[parser.getCurrent()];
  }

  if (curToken.getType() == TokenType::END) {
    throw std::runtime_error("NO STRING AFTER .\"!!!");
  }
  UserInterface::getInstance().displayMessage(str);

  if (curToken.getType() == TokenType::QUOTS) {
    parser.moveCurrent();
    return;
  }
}

// rot - циклически сдвинуть три верхние числа. 
// например, стек до: 4 1 2 3, стек после: 4 3 1 2
// over - скопировать второе число и положить копию над верхним.
// например, стек до: 3 2 1, стек после: 3 2 1 2

void RotExpr::execute(Forth& forth, std::vector<Token>& tokens){

}

void OverExpr::execute(Forth& forth, std::vector<Token>& tokens){
  
}

void CycleExpr::execute(Forth& forth, std::vector<Token>& tokens){

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
   std::string message(1, static_cast<char>(popped)); 
  UserInterface::getInstance().displayMessage(message);
}


void ConditionalExpr::execute(Forth &forth, std::vector<Token> &tokens) {
    Parser &parser = Parser::getInstance(tokens, forth);
    size_t savedPosition = parser.getCurrent();
    
    if (forth.pop()) {
    std::cout << "Doing if!" << std::endl;
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
    }
    } else {
      std::cout << "Doing else or then!" << std::endl;
      // find else or then
      while (parser.getCurrentToken().getLexeme() != "then" &&
             parser.getCurrentToken().getLexeme() != "else" &&
             parser.getCurrentToken().getType() != TokenType::END) {
        parser.dropToken(parser.getCurrent()); //we don't need that
      }
      // remove then or else
      if (parser.getCurrentToken().getLexeme() == "then") {
        while (parser.getCurrentToken().getType() != TokenType::SEMICOLON) {
          if (parser.getCurrentToken().getType() == TokenType::END) {
            throw std::runtime_error("No semicolon after if!");
          }
          parser.dropToken(parser.getCurrent());
        }
        return;
      }
      //remove else
      parser.dropToken(parser.getCurrent());
      savedPosition = parser.getCurrent();
      while (parser.getCurrentToken().getType() != TokenType::SEMICOLON &&
             parser.getCurrentToken().getLexeme() != "then" &&
             parser.getCurrentToken().getType() != TokenType::END) {
        parser.parse();
      }
      
       if (parser.getCurrentToken().getLexeme() == "then") {
        while (parser.getCurrentToken().getType() != TokenType::SEMICOLON) {
          if (parser.getCurrentToken().getType() == TokenType::END) {
            throw std::runtime_error("No semicolon after if!");
          }
          parser.dropToken(parser.getCurrent());
        }
        return;
      }
    }

  parser.dropToken(parser.getCurrent());
  // parser.placeCurrent(savedPosition);
  std::cout << "Current is " << tokens[parser.getCurrent()].getLexeme() << std::endl;
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
