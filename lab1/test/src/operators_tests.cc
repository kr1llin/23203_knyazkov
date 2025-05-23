#include "../../src/hashtable.cpp"
#include <gtest/gtest.h>

TEST(operators_tests, brackets_test_1) {
  HashTable a = HashTable();
  const Value value = {1, 1};
  a.insert("Key", value);
  EXPECT_TRUE(a["Key"] == value);
}

TEST(operators_tests, brackets_test_2) {
  HashTable a = HashTable();
  Value empty = Value();
  EXPECT_TRUE(empty == a["something"]);
}

TEST(operators_tests, copy_assignment_test_1) {
  HashTable a = HashTable();
  Value Value1 = {1, 1};
  Value Value2 = {2, 2};
  Value Value3 = {3, 3};

  a.insert("Key1", Value1);
  a.insert("Key2", Value2);

  HashTable b;
  b.insert("Key3", Value3);

  b = a;

  EXPECT_TRUE(b["Key1"] == Value1);
  EXPECT_TRUE(b["Key2"] == Value2);
  EXPECT_FALSE(b["Key3"] == Value3); // do not need to be here
}

TEST(operators_tests, copy_assignment_test_2) {
  HashTable a = HashTable();
  a = a;
  EXPECT_EQ(a.getSize(), 0);
}

TEST(operators_tests, copy_assignment_test_3) {
    HashTable a = HashTable();
    HashTable b = HashTable();

    b.insert("1", {1,1});
    b.insert("2", {2,2});

    a = b; 

    EXPECT_EQ(a.getSize(), 2); // Size should be 2
    EXPECT_EQ(a.getCapacity(), 10); // Capacity should remain the same
    EXPECT_TRUE(a.contains("1")); // Check if the value is copied correctly
    EXPECT_TRUE(a.contains("2"));
}

TEST(operators_tests, move_assignment_test_1) {
  HashTable a = HashTable();
  size_t init_size = a.getSize();
  size_t init_capacity = a.getCapacity();
  a = std::move(a);
  EXPECT_EQ(init_size, a.getSize());
  EXPECT_EQ(init_capacity, a.getCapacity());
}

TEST(operators_tests, move_assignment_test_2) {
  HashTable a = HashTable();
  HashTable b = HashTable(1);
  b.insert("K", {1, 1});
  size_t b_size = b.getSize();
  size_t b_capacity = b.getCapacity();
  a = std::move(b);

  EXPECT_EQ(b_size, a.getSize());
  EXPECT_EQ(b_capacity, a.getCapacity());
}

TEST(operators_tests, move_assignment_test_3) {
  HashTable a = HashTable();
  HashTable b = HashTable(1);
  b.insert("K", {1, 1});
  size_t b_size = b.getSize();
  size_t b_capacity = b.getCapacity();
  a = std::move(b);

  EXPECT_EQ(b_size, a.getSize());
  EXPECT_EQ(b_capacity, a.getCapacity());
}

TEST(operators_tests, move_assignment_test_4) {
  HashTable a = HashTable();
  HashTable b = HashTable(2);
  b.insert("K", {1, 1});

  a = std::move(b);
  EXPECT_TRUE(b.empty());
}

TEST(operators_tests, isEqual_test_1) {
  HashTable a = HashTable();
  HashTable b = HashTable();

  a.insert("KeyA", {1, 1});
  b.insert("KeyA", {1, 1});
  EXPECT_TRUE(a == b);
}

TEST(operators_tests, isEqual_test_2) {
  HashTable a = HashTable();
  HashTable b = HashTable();

  a.insert("KeyA", {1, 1});
  b.insert("KeyA", {2, 2});
  EXPECT_FALSE(a == b);
}

TEST(operators_tests, isEqual_test_3) {
  HashTable a = HashTable(1);
  HashTable b = HashTable(2);
  b.insert("random", {2, 2});

  EXPECT_FALSE(a == b);
}

TEST(operators_tests, isEqual_test_4) {
  HashTable a = HashTable(5);
  HashTable b = HashTable(5);
  b.insert("random", {2, 2});
  a.insert("random", {2, 2});
  b.insert("notSoRandom", {3, 3});
  EXPECT_FALSE(a == b);
  b.erase("notSoRandom");
  EXPECT_TRUE(a == b);
}

TEST(operators_tests, isNotEqual_test_1) {
  HashTable a = HashTable(1);
  HashTable b = HashTable(2);
  b.insert("random", {2, 2});

  EXPECT_TRUE(a != b);
  EXPECT_FALSE(a != a);
}
