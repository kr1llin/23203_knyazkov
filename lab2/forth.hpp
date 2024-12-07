#pragma once
#include "Token.hpp"
#include "interpreter.hpp"

#include <cstddef>
#include <iostream>
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
  Forth() {}

  void runFile(const std::string &path);
  void runPrompt();
  void run(const std::string &source);
  void error(int line, const std::string &message);
  void error(const Token &token, const std::string &message);

  void push(int value) { stack.push_back(value); }
  int pop();
  int peek() const;
  std::vector<int> getStack() const { return stack; }

  int loop_i{};

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
