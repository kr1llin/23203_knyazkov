#include "googletest/googlemock/include/gmock/gmock.h"
#include "googletest/googletest/include/gtest/gtest.h"

#include "../../src/forth.hpp"
#include "../../src/ExecutionContext.hpp"
#include "../../src/expressions.hpp"


#include "gmock/gmock.h"
#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>

class MockBufferManager : public ExecutionContext::BufferManager {
public:
    MOCK_METHOD(const std::string &, getBuffer, ());
    MOCK_METHOD(void, addToBuffer, (const std::string &str), ());
    MOCK_METHOD(void, clearBuffer, ());
    MOCK_METHOD(bool, isEmpty, (), (const));
};

// class MockStackManager : public ExecutionContext::StackManager {
// public:
//     MOCK_METHOD(void, push, (int value), (override));
//     MOCK_METHOD(int, pop, (), (override));
//     MOCK_METHOD(int, peek, (), (const, override));
//     MOCK_METHOD(const std::vector<int> &, getStack, (), (const, override));
// };

// class MockTokenManager : public ExecutionContext::TokenManager {
// public:
//     MOCK_METHOD(void, setTokens, (const std::vector<Token> &tkns), (override));
//     MOCK_METHOD(std::vector<Token> &, getTokens, (), (override));
//     MOCK_METHOD(void, dropToken, (size_t index), (override));
//     MOCK_METHOD(bool, match, (const std::initializer_list<TokenType> &types), (override));
//     MOCK_METHOD(void, placeCurrent, (size_t index), (override));
//     MOCK_METHOD(Token, getPreviousToken, (), (const, override));
//     MOCK_METHOD(Token, getCurrentToken, (), (const, override));
//     MOCK_METHOD(size_t, getCurrent, (), (const, override));
//     MOCK_METHOD(void, moveCurrent, (), (override));
//     MOCK_METHOD(bool, check, (TokenType type), (override));
//     MOCK_METHOD(const Token &, peekAtToken, (), (const, override));
//     MOCK_METHOD(const Token &, peekAtPreviousToken, (), (const, override));
//     MOCK_METHOD(bool, isAtEnd, (), (const, override));
//     MOCK_METHOD(const Token &, advance, (), (override));
//     MOCK_METHOD(const int &, getIterator, (), (const, override));
//     MOCK_METHOD(void, setLoopIterator, (int &value), (override));
// };

// Mock ExecutionContext
// class MockExecutionContext : public ExecutionContext {
// public:
//     MockExecutionContext(MockBufferManager &bufferManager,
//                          MockStackManager &stackManager,
//                          MockTokenManager &tokenManager)
//         : ExecutionContext(bufferManager, stackManager, tokenManager) {}
// };

class MockExecutionContext : public ExecutionContext {
public:
    explicit MockExecutionContext(MockBufferManager &bufferManager)
        : ExecutionContext(bufferManager) {}
};


//FIXTURE
class Fixture : public ::testing::Test {
protected:
  int sharedValue;

  void SetUp() override {
  }

  void TearDown() override {
  }
};


TEST_F(Fixture, Test1) {
}

TEST(TestREPL, Subtest_1) {
  auto forth = std::make_unique<Forth>();
  ExecutionContext context;

  EXPECT_THROW(forth->runFile("worng_path", context), std::runtime_error);
}

TEST(TestREPL, Subtest_2) {

}

TEST(CrTest, Subtest_1) {
  MockBufferManager mockBufferManager;
  CrExpr crExpr;

  MockExecutionContext context(mockBufferManager);

  // EXPECT_CALL(mockBufferManager, addToBuffer("\n"))
  //     .Times(1);
  crExpr.execute(context);
  EXPECT_EQ(context.getBufferManager().getBuffer(), "\n");
}

TEST(LoopTest, Subtest_1) {
  MockBufferManager mockBufferManager;
  MockExecutionContext context(mockBufferManager);
  auto forth = std::make_unique<Forth>();
  context.getTokenManager().setTokens();
  forth->run("10 0 do loop;\n", context);
  std::cout << "Here\n";
  UserInterface::printStack(context.getStackManager().getStack());
  CycleExpr cycle;
  cycle.execute(context);
  std::ostringstream buff;
  std::streambuf *oldCoutBuffer = std::cout.rdbuf(buff.rdbuf());
  UserInterface::printStack(context.getStackManager().getStack());
  std::cout.rdbuf(oldCoutBuffer);
  EXPECT_EQ(buff.str(), "<- Top\n");
}


// FOR REDIRECTING OUTPUT
TEST(CoutTest, CapturesOutput) {
  std::ostringstream buffer; 
  std::streambuf *oldCoutBuffer =
      std::cout.rdbuf(buffer.rdbuf());

 //Write to std::cout

  std::cout.rdbuf(oldCoutBuffer);

  EXPECT_EQ(buffer.str(), "Something something!\n");
}

int main(int argc, char **argv) {
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
