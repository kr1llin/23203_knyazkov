#include "../operators.cpp"
#include <gtest/gtest.h>

TEST(operators_tests, brackets_test_1){
    HashTable a = HashTable();
    const Value value = {1, 1};
    a.insert("Key", value);
    EXPECT_TRUE(a["Key"] == value);
}

TEST(operators_tests, brackets_test_2){
    HashTable a = HashTable();
    Value* empty = new Value();
    EXPECT_TRUE(*empty == a["something"]);
}

//(???) expect rehashing (new_size == old_size * 2)
TEST(operators_tests, brackets_test_3){
    HashTable a = HashTable(1);
    a.insert("something", {1,1});
    EXPECT_FALSE(a.insert("some", {1,1}));
}
