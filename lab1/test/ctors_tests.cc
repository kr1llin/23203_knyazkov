#include "../ctors.cpp"
#include <gtest/gtest.h>
#include <limits.h>
#include <stdexcept>

TEST(ctors_tests, empty_ctor_test){
    HashTable h = HashTable();
    EXPECT_EQ(0, h.getSize());
    EXPECT_EQ(0, h[""].weight);
    EXPECT_EQ(true, h.empty());
    ASSERT_EQ(DEF_CAPACITY, h.getCapacity());
}

TEST(ctors_tests, copy_cstor_test_1){
    HashTable a = HashTable();
    Value value = {1,1};
    a.insert("Key", value);
    HashTable b(a);
    EXPECT_EQ(true, a["Key"].age == b["Key"].age);
    EXPECT_EQ(true, a["Key"].weight == b["Key"].weight);
}

TEST(ctors_tests,copy_cstor_test_2){
    ASSERT_THROW(HashTable a = HashTable(SIZE_MAX), std::out_of_range);
}


