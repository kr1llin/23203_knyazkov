#include "../methods.cpp"
#include <exception>
#include <gtest/gtest.h>
#include <gtest/gtest_prod.h>
#include <string>

TEST(methods_tests, insert_test_1){
    HashTable a = HashTable();
    Value value = {1,1};
    const Key key = "Key";
    a.insert(key, value);
    ASSERT_TRUE(value == a[key]);
}

//INSERT ШАМАНИТ ЧТО-ТО
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
    a.insert("Kyeyyy", {1,1});
    EXPECT_EQ(6, a.getCapacity());
}

TEST(methods_tests, erase_test_1){
    HashTable a = HashTable(3);
    a.insert("Key", {1,1});
    EXPECT_TRUE(a.erase("Key"));
}

TEST(methods_tests, erase_test_2){
    HashTable a = HashTable(3);
    a.insert("Key", {1,1});
    a.erase("Key");
    EXPECT_EQ(0, a.getSize());
}

TEST(methods_tests, erase_test_3){
    HashTable a = HashTable(3);
    a.insert("Key", {1,1});
    a.erase("Key");
    EXPECT_FALSE(a.contains("Key"));
}

TEST(methods_tests, erase_test_4){
    HashTable a = HashTable(3);
    a.insert("Key", {1,1});
    EXPECT_FALSE(a.erase("Yek"));
}

TEST(methods_tests, erase_test_5){
    HashTable a = HashTable(3);
    a.insert("Key", {1,1});
    a.erase("Key");
    EXPECT_FALSE(a.erase("Key"));
}
