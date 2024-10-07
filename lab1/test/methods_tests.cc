#include "../methods.cpp"
#include <gtest/gtest.h>
#include <string>

TEST(methods_tests, insert_test_1){
    HashTable a = HashTable();
    Value value = {1,1};
    const Key key = "Key";
    a.insert(key, value);
    ASSERT_TRUE(value == a[key]);
}

TEST(methods_tests, insert_test_2){
    HashTable a = HashTable();
    Value value = {1, 1};
    const Key key  = "Key";
    a.insert(key, value);
    EXPECT_EQ(1, a.getSize()) << "Size hasn't been updated!!\n";
}

TEST(methods_tests, insert_test_3){
    HashTable a = HashTable();
    HashNode node = HashNode("Key", {2,2});
    a.insert(node.key, node.value);
    EXPECT_TRUE(a.find("Key") != -1) << "\"Key\" wasn't found!!\n";
}

TEST(methods_tests, insert_test_4){
    HashTable a = HashTable();

    int number = a.getCapacity();
    for (int i = 0; i < number; i++) {
        HashNode node = HashNode(std::to_string(i), {2,2});
        a.insert(node.key, node.value);
    }
    EXPECT_EQ(number , a.getSize()) << "size wasn't increased!!";
}

TEST(methods_tests, rehashing_test_1){
    HashTable a = HashTable(3);
    a.insert("Key", {1,1});
    a.insert("Keyy", {1,1});
    a.insert("Kyeyy", {1,1});
    a.insert("Kyeyy", {1,1});
    EXPECT_EQ(6, a.getCapacity());
  //NEW TABLE != nullptr or catche bad_alloc

  //TEST IF OLD TABLE IN NEWTABLE (ALL IT'S ELEMENTS)

  //CHECK IF OLD TABLE IS REALLY DESTROYED 
}
