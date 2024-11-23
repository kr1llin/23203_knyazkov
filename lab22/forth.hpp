#pragma once
#include "Token.hpp"
#include "definition.hpp"
#include "interpreter.hpp"

#include <cstddef>
#include <iostream>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::exception;
using std::isspace;
using std::ptrdiff_t;
using std::runtime_error;
using std::size_t;
using std::string;

class Forth {
public:
  // instance of Forth
  Forth() {}
  void runFile(const std::string &path);
  void runPrompt();
  void run(const std::string &source);
  void error(int line, const std::string &message);
  void error(const Token &token, const std::string &message);

  void push(int value) {
    stack.push_back(value);
  }

  void printStack() const {
    for (auto i : stack){
        std::cout << i << " ";
    }
    std::cout << "<- Top" << std::endl;
  }

  int pop() {
    if (stack.empty())
      throw std::runtime_error("Stack underflow");
    int value = stack.back();
    stack.pop_back();
    return value;
  }

  int peek() const {
    if (stack.empty())
      throw std::runtime_error("Stack is empty");
    return stack.back();
  }

private:
  void report(int line, const std::string &where, const std::string &message);
  std::vector<int> stack;
  bool hadError = false;
};

// //will be passed to the scanner and parser
// class ErrorReporter {
// public:
//   static bool hadError;

// private:
//   static void error(int line, const std::string &message);
//   static void report(int line, const std::string &where,
//                      const std::string &message);
// };

// class Scanner:Forth {

// };
