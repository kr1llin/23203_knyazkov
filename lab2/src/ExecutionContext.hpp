#pragma once

#include "Token.hpp"
#include <memory>
#include <string>
#include <vector>

// stores data of current forth execution
class ExecutionContext {
public:
  // nested class for managing the message buffer
  class BufferManager {
  public:
    const std::string &getBuffer() const;
    void addToBuffer(const std::string &str);
    void clearBuffer();
    bool isEmpty() const;

  private:
    std::string buffer; // the message itself
  };

  // nested class for managing the stack
  class StackManager {
  public:
    void push(int value);
    int pop();
    int peek() const;
    const std::vector<int> &getStack() const;

  private:
    std::vector<int> stack; // stack itself
  };

  // nested class for managing tokens
  class TokenManager {
  public:
    void setTokens(const std::vector<Token> &tkns);
    std::vector<Token> &getTokens();
    void dropToken(size_t index);
    bool match(const std::initializer_list<TokenType> &types);

    void placeCurrent(size_t index);
    Token getPreviousToken() const; // remove?
    Token getCurrentToken() const;  // remove?
    size_t getCurrent() const;
    void moveCurrent() { current++; }
    bool check(TokenType type) const;
    const Token &peekAtToken() const;
    const Token &peekAtPreviousToken() const;
    bool isAtEnd() const;
    const Token &advance();

    const int &getIterator() const;
    void setLoopIterator(int value);

  private:
    std::vector<Token> tokens; // tokens!
    size_t current = 0;        // current token index
    int loop_i = 0;            // loop status
  };

  // public interface for the ExecutionContext
  BufferManager &getBufferManager() { return messageBuffer; }
  StackManager &getStackManager() { return stack; }
  TokenManager &getTokenManager() { return tokenManager; }

  // error status manipulations
  bool hadError() const;
  void setErrorStatus(bool b);

  explicit ExecutionContext(BufferManager &buff)
      : messageBuffer(buff){}
  ExecutionContext() = default;

private:
  BufferManager messageBuffer;
  StackManager stack;
  TokenManager tokenManager;

  bool errorStat = false; // error status
};



// class IBufferManager {
// public:
//     virtual const std::string &getBuffer() const = 0;
//     virtual void addToBuffer(const std::string &str) = 0;
//     virtual void clearBuffer() = 0;
//     virtual bool isEmpty() const = 0;
//     virtual ~IBufferManager() = default;
// };

// class IStackManager {
// public:
//     virtual void push(int value) = 0;
//     virtual int pop() = 0;
//     virtual int peek() const = 0;
//     virtual const std::vector<int> &getStack() const = 0;
//     virtual ~IStackManager() = default;
// };

// class ITokenManager {
// public:
//     virtual void setTokens(const std::vector<Token> &tkns) = 0;
//     virtual std::vector<Token> &getTokens() = 0;
//     virtual void dropToken(size_t index) = 0;
//     virtual bool match(const std::initializer_list<TokenType> &types) = 0;

//     virtual void placeCurrent(size_t index) = 0;
//     virtual size_t getCurrent() const = 0;
//     virtual void moveCurrent() = 0;
//     virtual bool check(TokenType type) const = 0;
//     virtual const Token &peekAtToken() const = 0;
//     virtual const Token &peekAtPreviousToken() const = 0;
//     virtual bool isAtEnd() const = 0;
//     virtual const Token &advance() = 0;

//     virtual const int &getIterator() const = 0;
//     virtual void setLoopIterator(int value) = 0;
//     virtual ~ITokenManager() = default;
// };

// class BufferManager : IBufferManager{
//   public:
//     const std::string &getBuffer() const override;
//     void addToBuffer(const std::string &str) override;
//     void clearBuffer() override;
//     bool isEmpty() const override;

//   private:
//     std::string buffer; // the message itself
//   };

// class StackManager : IStackManager{
//   public:
//     void push(int value) override;
//     int pop() override;
//     int peek() const override;
//     const std::vector<int> &getStack() const override;

//   private:
//     std::vector<int> stack; // stack itself
//   };

// class TokenManager : ITokenManager{
//   public:
//     void setTokens(const std::vector<Token> &tkns) override;
//     std::vector<Token> &getTokens() override;
//     void dropToken(size_t index) override;
//     bool match(const std::initializer_list<TokenType> &types) override;

//     void placeCurrent(size_t index) override;
//     Token getPreviousToken() const; // remove?
//     Token getCurrentToken() const;  // remove?
//     size_t getCurrent() const override;
//     void moveCurrent() override { current++; }
//     bool check(TokenType type) const override;
//     const Token &peekAtToken() const override;
//     const Token &peekAtPreviousToken() const override;
//     bool isAtEnd() const override;
//     const Token &advance() override;

//     const int &getIterator() const override;
//     void setLoopIterator(int value) override;

//   private:
//     std::vector<Token> tokens; // tokens!
//     size_t current = 0;        // current token index
//     int loop_i = 0;            // loop status
//   };

//   class ExecutionContext {
//   public:
//     ExecutionContext(std::unique_ptr<IBufferManager> buff,
//                      std::unique_ptr<IStackManager> stk,
//                      std::unique_ptr<ITokenManager> tkn)
//         : messageBuffer(std::move(buff)), stack(std::move(stk)), tokenManager(std::move(tkn)) {}

//     IBufferManager &getBufferManager() { return *messageBuffer; }
//     IStackManager &getStackManager() { return *stack; }
//     ITokenManager &getTokenManager() { return *tokenManager; }

//     bool hadError() const { return errorStat; }
//     void setErrorStatus(bool b) { errorStat = b; }

//   private:
//     std::unique_ptr<IBufferManager> messageBuffer;
//     std::unique_ptr<IStackManager> stack;
//     std::unique_ptr<ITokenManager> tokenManager;

//     bool errorStat = false; // Error status
//   };













// class ExecutionContext {
// public:

//   //Manipulatons with message buffer
//   const std::string getBuffer() const;
//   void addToBuffer(const std::string &str);
//   void clearBuffer();
//   int &getIterator();
//   bool bufferIsEmpty();

//   //Manipulations with error status
//   bool hadError();
//   void setErrorStatus(bool b);

//   //Manipulations with stack
//   std::vector<int> getStack() const;
//   void push(int value);
//   int pop();
//   int peek() const;

  // Manipulations with tokens
  // void setTokens(const std::vector<Token> &tkns);
  // void resetTokens(std::vector<Token> &newTokens);
  // std::vector<Token> &getTokens();
  // void dropToken(size_t index);
  // void placeCurrent(size_t index);
  // Token getPreviousToken() const; //remove?
  // Token getCurrentToken() const; //remove?
  // size_t getCurrent() const;
  // void moveCurrent() { current++; }
  // bool check(TokenType type);
  // const Token &peekAtToken() const;
  // const Token &peekAtPreviousToken() const;
  // bool isAtEnd() const;
  // const Token &advance();
  // bool match(const std::initializer_list<TokenType> &types);

//   void setLoopIterator(int& value){loop_i = value;}

// private:
//   std::string buffer; // for messages
//   std::vector<int> stack; // for values
//   std::vector<Token> tokens; // for tokens

//   size_t current = 0; //current token
  // int loop_i = 0; //loop status
//   bool errorStat = false;
// };
