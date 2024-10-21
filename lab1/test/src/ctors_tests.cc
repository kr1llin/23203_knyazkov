#include "../src/ctors.cpp"
#include <gtest/gtest.h>
#include <limits.h>
#include <stdexcept>

TEST(ctors_tests, empty_ctor_test) {
  HashTable h = HashTable();
  EXPECT_EQ(0, h.getSize());
  EXPECT_EQ(0, h[""].weight);
  EXPECT_EQ(true, h.empty());
  ASSERT_EQ(DEF_CAPACITY, h.getCapacity());
}

TEST(ctors_tests, copy_cstor_test_1) {
  HashTable a = HashTable();
  Value value = {1, 1};
  a.insert("Key", value);
  HashTable b(a);
  EXPECT_EQ(true, a["Key"].age == b["Key"].age);
  EXPECT_EQ(true, a["Key"].weight == b["Key"].weight);
}

TEST(ctors_tests, copy_cstor_test_2) {
  ASSERT_THROW(HashTable a = HashTable(0), std::invalid_argument);
}

TEST(ctors_tests, capacity_cstor_test_1) {
  size_t init_capacity = 10;
  HashTable a = HashTable();

  EXPECT_EQ(init_capacity, a.getCapacity());
  EXPECT_EQ(0, a.getSize());
}

TEST(ctors_tests, capacity_cstor_test_2) {
  EXPECT_THROW({ HashTable a(0); }, std::invalid_argument);
}

TEST(ctors_tests, move_cstor_test_1) {
  HashTable a = HashTable();

  // Move construct a new HashTable from ht1
  HashTable b(std::move(a));

  EXPECT_EQ(10, b.getCapacity());
  EXPECT_EQ(0, b.getSize());

  EXPECT_EQ(a.getCapacity(), 0);
  EXPECT_EQ(a.getSize(), 0);
}

TEST(ctors_tests, move_cstor_test_2) {
  HashTable a = HashTable();
  const Value value1 = {1, 1};
  const Value value2 = {2, 2};
  a.insert("key1", value1);
  a.insert("key2", value2);

  HashTable b(std::move(a));

  EXPECT_EQ(2, b.getSize());
  EXPECT_EQ(value1.age, b["key1"].age);
  EXPECT_EQ(value1.weight, b["key1"].weight);

  EXPECT_EQ(value2.age, b["key2"].age);
  EXPECT_EQ(value2.weight, b["key2"].weight);

  EXPECT_EQ(0, a.getCapacity());
  EXPECT_EQ(0, a.getSize());
}
