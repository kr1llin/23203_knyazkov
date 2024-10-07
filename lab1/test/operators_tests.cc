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

TEST(operators_tests, copy_assignment_test_1){
   HashTable a = HashTable();
   Value Value1 = {1,1};
   Value Value2 = {2,2};
   Value Value3 = {3,3};

    a.insert("Key1", Value1);
    a.insert("Key2", Value2);
    

    HashTable b;
    b.insert("Key3", Value3);

    b = a;

    EXPECT_TRUE(b["Key1"] == Value1);
    EXPECT_TRUE(b["Key2"] == Value2);
    EXPECT_FALSE(b["Key3"] == Value3); // do not need to be here
}
