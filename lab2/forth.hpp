#pragma once
#include "Token.hpp"
#include "interpreter.hpp"
#include <string>
#include <vector>


class Forth {
public:
  Forth() {}

  // add string to forth's buffer output
  void addToBuffer(const std::string &str);
  void clearBuffer();

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
  std::string buffer{}; // for messages
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
