#include "ExecutionContext.hpp"
#include <algorithm>
#include <stdexcept>

// STACK MANAGER METHODS 
int ExecutionContext::StackManager::pop() {
  if (stack.empty()) {
    throw std::out_of_range("Stack is empty");
}
  int value = stack.back();
  stack.pop_back();
  return value;
}

int ExecutionContext::StackManager::peek() const {
  if (stack.empty()) {
    throw std::out_of_range("Stack is empty");
  }
  return stack.back();
}

void ExecutionContext::StackManager::push(int value) { stack.push_back(value); }

const std::vector<int> &ExecutionContext::StackManager::getStack() const {
  return stack;
}

// BUFFER MANAGER METHODS
bool ExecutionContext::BufferManager::isEmpty() const { return buffer.empty(); }

const std::string &ExecutionContext::BufferManager::getBuffer() const {
  return buffer;
}

void ExecutionContext::BufferManager::addToBuffer(const std::string &str) {
  buffer += str;
}

void ExecutionContext::BufferManager::clearBuffer() { buffer.clear(); }


// TOKEN MANAGER METHODS

void ExecutionContext::TokenManager::dropToken(size_t index) {
  if (index < tokens.size()) {
    tokens.erase(tokens.begin() + index);
  }
}

bool ExecutionContext::TokenManager::match(
    const std::initializer_list<TokenType> &types) {
  if (std::any_of(types.begin(), types.end(),
                  [this](TokenType type) { return check(type); })) {
    advance();
    return true;
  }

  return false;
}

// void ExecutionContext::resetTokens(std::vector<Token> &newTokens) {
//   tokens = newTokens;
//   current = 0;
// }

void ExecutionContext::TokenManager::setTokens(const std::vector<Token> &tkns) {
  tokens = tkns;
  current = 0;
}

bool ExecutionContext::TokenManager::check(TokenType type) const {
  return !isAtEnd() && peekAtToken().getType() == type;
}

const Token &ExecutionContext::TokenManager::advance() {
  return !isAtEnd() ? tokens[++current] : peekAtPreviousToken();
}

bool ExecutionContext::TokenManager::isAtEnd() const {
  return (current == tokens.size());
}

const Token &ExecutionContext::TokenManager::peekAtToken() const {
  if (isAtEnd()) {
    throw std::out_of_range("Attempted to peek at the end of the token list");
  }
  return tokens[current];
}

const Token &ExecutionContext::TokenManager::peekAtPreviousToken() const {
  if (current == 0) {
    throw std::out_of_range("No previous token available.");
  }
  return tokens[current - 1];
}

std::vector<Token> &ExecutionContext::TokenManager::getTokens() {
  return tokens;
}
size_t ExecutionContext::TokenManager::getCurrent() const { return current; }

Token ExecutionContext::TokenManager::getPreviousToken() const {
  return peekAtPreviousToken();
}
Token ExecutionContext::TokenManager::getCurrentToken() const {
  return tokens[current];
}
void ExecutionContext::TokenManager::placeCurrent(size_t index) {
  current = index;
}

const int &ExecutionContext::TokenManager::getIterator() const {
  return loop_i;
}
void ExecutionContext::TokenManager::setLoopIterator(int value) {
  loop_i = value;
}

// ERRORS

void ExecutionContext::setErrorStatus(bool b) { errorStat = b; }

bool ExecutionContext::hadError() const { return errorStat; }










//DUMPSTER

// // if error - run to the end of expression
// void ExecutionContext::synchronize() {
//   advance();

//   while (!isAtEnd()) {
//     if (peekAtPreviousToken().getType() == TokenType::SEMICOLON)
//       return;

//     switch (peekAtToken().getType()) {
//     case TokenType::FOR:
//     case TokenType::IF:
//     case TokenType::WHILE:
//     case TokenType::DQUOTS:
//       return;
//     default:
//       break;
//     }
//     advance();
//   }
// }
