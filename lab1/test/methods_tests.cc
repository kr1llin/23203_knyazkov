#include "../methods.cpp"
#include <gtest/gtest.h>

TEST(methods_tests, insert_test_1){
    HashTable a = HashTable();
    Value value = {1,1};
    const Key key = "Key";
    a.insert(key, value);
    ASSERT_TRUE(value == a[key]);
}

TEST(methods_tests, insert_test_2){
    HashTable a = HashTable();
    std::cout << "a: size = " << a.getSize() << ", capacity = " << a.getCapacity();
    Value value = {1, 1};
    const Key key  = "Key";
    a.insert(key, value);
    ASSERT_EQ(1, a.getSize()) << "Size hasn't been updated!!\n";
}
