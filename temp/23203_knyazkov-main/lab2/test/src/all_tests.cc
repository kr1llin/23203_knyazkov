#include <iostream>
#include <sstream>
#include <string>
#include "../../forth.cpp"

#include <gtest/gtest.h>

// Function to be tested
void printMessage() {
    std::cout << "Hello, World!" << std::endl;
}

// Test fixture class
class OutputTest : public ::testing::Test {
protected:
    std::ostringstream buffer;
    std::streambuf* oldCout;

    void SetUp() override {
        // Redirect cout to the stringstream
        oldCout = std::cout.rdbuf(buffer.rdbuf());
    }

    void TearDown() override {
        // Restore cout
        std::cout.rdbuf(oldCout);
    }
};

// Test case
TEST_F(OutputTest, TestPrintMessage) {
    printMessage(); // Call the function that prints to cout

    // Check the output
    std::string output = buffer.str();
    EXPECT_EQ(output, "Hello, World!\n"); // Verify the output
}

// int main(int argc, char** argv) {
//     ::testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }
