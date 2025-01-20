#include "forth.hpp"
#include "ExecutionContext.hpp"
#include "Token.hpp"
#include "interpreter.hpp"
#include "scanner.hpp"

#include <cstdio>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>

int Forth::executeForth(int argc, const char **argv) {
  auto forth = std::make_unique<Forth>();
  auto context = std::make_unique<ExecutionContext>(); // init context for
                                                       // current execution
  if (argc > 2) {
    std::cerr << "Lot of arguments!\n quit" << std::endl;
    return -1;
  }
  if (argc == 2) {
    forth->runFile(argv[1], *context);
  } else {
    forth->runPrompt(*context);
  }
  return 0;
}

void Forth::runFile(const std::string &path, ExecutionContext &context) {
  std::ifstream file(path);
  if (!file) {
    throw std::runtime_error("Could not open file: " + path);
  }

  std::ostringstream oss;
  std::string str;

  while (std::getline(file, str)) {
    if (!str.empty()) {
      oss << str << " ";
    }
  }

  std::string combinedStr = oss.str();
  run(combinedStr, context);

  if (context.hadError()) {
    exit(1);
  }
  context.setErrorStatus(false);
}

void Forth::runPrompt(ExecutionContext &context) {
  string line;

  while (true) {
    std::string line = UserInterface::getUserInput();
    if (line.empty()) {
      break;
    }
    run(line, context);
    context.setErrorStatus(false);
  }
}

void Forth::run(const string& source, ExecutionContext& context){
    auto scanner = std::make_unique<Scanner>(source);
    context.getTokenManager().setTokens(scanner->scanTokens());
    Interpreter interpretator(&context);
    interpretator.interprete();
    // Interpreter::interprete(context);

    context.getBufferManager().addToBuffer(
        context.getBufferManager().isEmpty() ? "ok" : " ok");
    UserInterface::displayMessage(context.getBufferManager().getBuffer());
    context.getBufferManager().clearBuffer();
    UserInterface::printStack(context.getStackManager().getStack());

    if (context.hadError()) {
      return;
    }

    // // temp
    // for (const Token& token : context.getTokenManager().getTokens()) {
    //   std::cout << token.toString() << std::endl;
    // }
}

void Forth::error(const Token &token, const std::string &message, ExecutionContext& context) {
  if (token.getType() == TokenType::END) {
    report(token.getLine(), " at end", message, context);
  } else {
    report(token.getLine(), " at '" + token.getLexeme() + "'", message, context);
  }
}

void Forth::error(int line, const string& message, ExecutionContext& context){
    report(line, "", message, context);
}

void Forth::report(int line, const std::string &where, const std::string &message, ExecutionContext& context) {
    std::cerr << "[line " + std::to_string(line) + "] Error" + where + ": " + message << std::endl;
    context.setErrorStatus(true);
}











// Команды интерпретатора вываливаются из фабрики
// unique_pointers (to vector elements-units), чтобы сама фабрика делала эти поинтеры
// инкапсуляция (namespace)
//

// STD::OUT ПЕРЕОПРЕДЕЛИТЬ, ЧТОБЫ ОН ВЫВОД ПИСАЛ И В ФАЙЛ, ЧТОБЫ ПРОВЕРЯТЬ
// НАПИСАЛА ПРОГРАММА ИЛИ НЕТ (ПЕРЕНАПРАВЛЕНИЕ ФАЙЛА)
//
// User Interface (разные части программы, которые взаимодействуют друг с другом
// ЭТО ВЫВОД НА ЭКРАН), business logic (весь жир, интерпретатор)
//
//GMOCK


  // //temporary
  //   for (Token token:tokens){
  //       cout << token.toString() << endl;
  //   }

// read word from input
// look up word in dictionary
// if found {
//   if state = interpret OR word header has immediate flag {
//     execute word
//   } else {
//     compile word
//   }
// } else {
//   if valid number under current base {
//     if state = interpret {
//       push number to stack
//     } else {
//       compile LIT
//       compile number
//     }
//   } else {
//     error "unknown word 'something-something'"
//   }
// }

//for run
    // for (auto t = tokens.begin(); t != std::prev(tokens.end()); ++t) {
    //   Token token = *t;
    //   std::unique_ptr<Expr> expression = parser->parse();
    //   std::cout << "Expression is " << expression.get() << std::endl;
    //   if (expression != nullptr) {
    //     expression->execute(*this); 
    //     executedTokens.push_back(token); 
    //     std::cout << "Processed token " << token.getLexeme() << std::endl;

    //   }
    // } // else {
      //    std::cerr << "Error: Failed to parse expression at token index " <<
      //    i
      //              << "." << std::endl;
      //   return;
      //  }

    // else {
    //     std::cerr << "Error: Failed to parse expression." << std::endl;
    // }
    //delete expression
