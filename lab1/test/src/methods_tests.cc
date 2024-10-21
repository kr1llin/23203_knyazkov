#include "../src/methods.cpp"
#include <gtest/gtest.h>
#include <gtest/gtest_prod.h>
#include <string>

TEST(methods_tests, insert_test_1) {
  HashTable a = HashTable();
  Value value = {1, 1};
  const Key key = "Key";
  a.insert(key, value);
  ASSERT_TRUE(value == a[key]);
}

TEST(methods_tests, insert_test_2) {
  HashTable a = HashTable();
  Value value = {1, 1};
  const Key key = "Key";
  a.insert(key, value);

  EXPECT_EQ(1, a.getSize()) << "Size hasn't been updated!!\n";
}

TEST(methods_tests, insert_test_3) {
  HashTable a = HashTable();
  HashNode node = HashNode("Key", {2, 2});
  a.insert(node.key, node.value);
  EXPECT_TRUE(a.find("Key") != -1) << "\"Key\" wasn't found!!\n";
}

TEST(methods_tests, insert_test_4) {
  HashTable a = HashTable();
  int number = a.getCapacity();

  for (int i = 0; i < number; i++) {
    HashNode node = HashNode(std::to_string(i), {2, 2});
    a.insert(node.key, node.value);
  }
  EXPECT_EQ(number, a.getSize()) << "size wasn't increased!!";
}

TEST(methods_tests, rehashing_test_1) {
  HashTable a = HashTable(4);
  a.insert("Key", {1, 1});
  a.insert("Key1", {1, 2});
  a.insert("Key2", {5, 1});
  a.insert("Key3", {1, 9});
  EXPECT_EQ(8, a.getCapacity());
}

TEST(methods_tests, erase_test_1) {
  HashTable a = HashTable(3);
  a.insert("Key", {1, 1});
  EXPECT_TRUE(a.erase("Key"));
}

TEST(methods_tests, erase_test_2) {
  HashTable a = HashTable(3);
  a.insert("Key", {1, 1});
  a.erase("Key");
  EXPECT_EQ(0, a.getSize());
}

TEST(methods_tests, erase_test_3) {
  HashTable a = HashTable(3);
  a.insert("Key", {1, 1});
  a.erase("Key");
  EXPECT_FALSE(a.contains("Key"));
}

TEST(methods_tests, erase_test_4) {
  HashTable a = HashTable(3);
  a.insert("Key", {1, 1});
  EXPECT_FALSE(a.erase("Yek"));
}

TEST(methods_tests, erase_test_5) {
  HashTable a = HashTable(3);
  a.insert("Key", {1, 1});
  a.erase("Key");
  EXPECT_FALSE(a.erase("Key"));
}

TEST(methods_tests, linear_probing_test_1) {
  HashTable a = HashTable();
  Key key = "testKey";
  int result = a.linearProbing(0, key);
  EXPECT_EQ(0, result);
}

TEST(methods_tests, linear_probing_test_2) {
  HashTable a = HashTable();
  Key key = "testKey";
  Value value = {1, 1};
  a.insert(key, value);

  int startIndex = a.find(key);
  int result = a.linearProbing(startIndex, key);
  EXPECT_EQ(result, startIndex);
}

TEST(methods_tests, linear_probing_test_3) {
  HashTable a = HashTable();

  Key key1 = "testKey1";
  Value value1 = {1, 1};
  Key key2 = "testKey2";
  Value value2 = {2, 2};

  a.insert(key1, value1);
  a.insert(key2, value2);

  int startIndex = a.find(key1);
  int result = a.linearProbing(startIndex, key2);
  EXPECT_NE(result, startIndex);
}

TEST(methods_tests, linear_probing_test_4) {
  HashTable a = HashTable();
  for (int i = 0; i < a.getCapacity(); i++) {
    Key key = "key" + std::to_string(i);
    Value value = {1, 1};
    a.insert(key, value);
  }

  // Now the table is full, so probing should not find a suitable index
  Key newKey = "newKey";
  int startIndex = 0;
  int result = a.linearProbing(startIndex, newKey);
  EXPECT_EQ(result, -1);
}

TEST(methods_tests, linear_probing_test_5) {
  HashTable a = HashTable();

  Key key1 = "key1";
  Key key2 = "key2";
  Key key3 = "key3";

  a.insert(key1, {1, 1});
  a.insert(key2, {1, 1});
  a.insert(key3, {1, 1});

  // Assuming a collision occurs, we want to find the next available slot
  int startIndex = a.find(key1);
  int result = a.linearProbing(startIndex, key2);
  EXPECT_NE(result, startIndex);
}


TEST(methods_tests, clear_test_1) {
  HashTable a = HashTable();
  a.insert("key", {1, 1});
  a.insert("Key2", {2, 2});

  EXPECT_EQ(a.getSize(), 2);

  a.clear();

  EXPECT_EQ(a.getSize(), 0);
}

TEST(methods_tests, clear_test_2) {
  HashTable a = HashTable(1);
    a.clear();

    EXPECT_NO_THROW({
     a.clear();
    });
}
