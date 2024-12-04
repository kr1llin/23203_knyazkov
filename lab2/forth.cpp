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

#include "forth.hpp"
#include "Token.hpp"
#include "UserInterface.hpp"
#include "parser.hpp"
#include "scanner.hpp"


#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>
#include <tclap/CmdLine.h>
#include <vector>

void Forth::runFile(const std::string& path) {
    std::ifstream file(path);
    if (!file) {
        throw std::runtime_error("Could not open file: " + path);
    }
    string str, filecontent;

    while (getline(file, str)){
        filecontent += str;
        filecontent.push_back('\n');
    }

    run(filecontent);
    if (hadError){
        exit(65); //collapse!
    }
}

void Forth::error(const Token &token, const std::string &message) {
  if (token.getType() == TokenType::END) {
    report(token.getLine(), " at end", message);
  } else {
    report(token.getLine(), " at '" + token.getLexeme() + "'", message);
  }
}

void Forth::runPrompt(){
    string line;

    while (true){
        UserInterface::getInstance().putG();
        std::string line = UserInterface::getInstance().getUserInput();
        if (line.empty()) break;
        run(line);
        std::cout << "------------------------" << std::endl;
        UserInterface::getInstance().printStack(*this);
        std::cout << "------------------------" << std::endl;

        hadError = false;
    }
}

void Forth::run(const string& source){
    Scanner* scanner = new Scanner(source);
    std::vector<Token> tokens = scanner->scanTokens();
    
    Parser& parser = Parser::getInstance(tokens, *this);
    // tokens = parser.getTokens(); //for debugging
    parser.resetTokens(tokens);
    parser.parse();
 
    if (hadError) return;

    //temporary
    for (Token token:tokens){
        cout << token.toString() << endl;
    }
}

void Forth::error(int line, const string& message){
    report(line, "", message);
}

void Forth::report(int line, const std::string &where, const std::string &message) {
    std::cerr << "[line " + std::to_string(line) + "] Error" + where + ": " + message << std::endl;
    hadError = true;
}

int main(int argc, const char **argv) {
  Forth *forth = new Forth();
  try {
    size_t commandLineArgCount = static_cast<size_t>(argc);
    auto commandLineArgVector = argv;
    if (argc > 1) {
      std::cerr << "Lot of arguments!\n quit" << std::endl;
      return -1;
    }
    if (argc == 2) {
      forth->runFile(argv[1]);
    } else {
      forth->runPrompt();
    }

    return 0;
  } catch (const std::exception &ex) {
    cerr << "forth: " << ex.what() << endl;
    return -1;
  }
}


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
