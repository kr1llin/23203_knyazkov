#pragma once
#include "Token.hpp"
#include <string>
#include <vector>
#include "ExecutionContext.hpp"


class Forth {
public:
  Forth() = default;

  static int executeForth(int argc, const char **argv);
  void runFile(const std::string &path, ExecutionContext& context);
  void runPrompt(ExecutionContext& context);
  void run(const std::string &source, ExecutionContext& context);
  void error(int line, const std::string &message, ExecutionContext& context);
  void error(const Token &token, const std::string &message, ExecutionContext& context);

private:
  void report(int line, const std::string &where, const std::string &message, ExecutionContext& context);
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
