#pragma GCC diagnostic ignored "-Wself-move"
#include "../../src/hashtable.cpp"
#include <gtest/gtest.h>
#include <gtest/gtest_prod.h>
#include <limits.h>
#include <stdexcept>

TEST(ctors_tests, empty_ctor_test) {
  HashTable h = HashTable();
  EXPECT_EQ(0, h.getSize());
  EXPECT_EQ(true, h.empty());
  ASSERT_EQ(10, h.getCapacity());
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

}

TEST(ctors_tests, move_cstor_test_2) {
  HashTable a = HashTable();
  const Value value1 = {1, 1};
  const Value value2 = {2, 2};
  a.insert("key1", value1);
  a.insert("key2", value2);

  HashTable b(std::move(a));

  std::clog << "b.capacity and size is :" << b.getCapacity() << " "
            << b.getSize() << std::endl;

  EXPECT_EQ(2, b.getSize());
  EXPECT_EQ(value1.age, b["key1"].age);
  EXPECT_EQ(value1.weight, b["key1"].weight);

  EXPECT_EQ(value2.age, b["key2"].age);
  EXPECT_EQ(value2.weight, b["key2"].weight);
}

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

  b.insert("1", {1, 1});
  b.insert("2", {2, 2});

  a = b;

  EXPECT_EQ(a.getSize(), 2);
  EXPECT_EQ(a.getCapacity(), 10);
  EXPECT_TRUE(a.contains("1"));
  EXPECT_TRUE(a.contains("2"));
}

// assignment to itself
// TEST(operators_tests, move_assignment_test_1) {
//   HashTable a = HashTable();
//   size_t init_size = a.getSize();
//   size_t init_capacity = a.getCapacity();
//   a = std::move(a);
//   EXPECT_EQ(init_size, a.getSize());
//   EXPECT_EQ(init_capacity, a.getCapacity());
// }

TEST(operators_tests, move_assignment_test_2) {
  HashTable a = HashTable();
  HashTable b(1);
  b.insert("K", {1, 1});
  size_t b_size = b.getSize();
  size_t b_capacity = b.getCapacity();
  a = std::move(b);

  EXPECT_EQ(b_size, a.getSize());
  EXPECT_EQ(b_capacity, a.getCapacity());
}

TEST(operators_tests, move_assignment_test_3) {
  HashTable a = HashTable();
  EXPECT_NO_THROW(a = std::move(a));
}

TEST(operators_tests, move_assignment_test_4) {
  HashTable a = HashTable();
  HashTable b = HashTable(2);
  size_t init_b_size = b.getSize();

   int number = 100;
  for (int i = 1; i < number - 1; i += 2) {
    a.insert(std::to_string(i), {2, 2});
  }

  a = std::move(b);
  // EXPECT_TRUE(b.empty());
  EXPECT_EQ(init_b_size, a.getSize());

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
  HashTable a = HashTable();
  HashTable b = HashTable();
  b.insert("random", {2, 2});

  EXPECT_FALSE(a == b);
}

TEST(operators_tests, isEqual_test_4) {
  HashTable a = HashTable(5);
  HashTable b = HashTable(5);
  b.insert("random", {2, 2});
  a.insert("random", {2, 2});
  b.insert("notSoRandom", {3, 3});
  EXPECT_TRUE(a != b);
  b.erase("notSoRandom");
  EXPECT_TRUE(a == b);
}

TEST(operators_tests, isEqual_test_5) {
  HashTable a = HashTable(5);
  HashTable b = HashTable(5);

  int number = 100;
  for (int i = 0; i <= number; i++) {
    std::clog << "size = " << a.getSize() <<std::endl;
    a.insert(std::to_string(i), {2, 2});
    EXPECT_TRUE(a != b);
  }
  for (int i = 0; i <= number; i++) {
    EXPECT_TRUE(a != b);
    a.erase(std::to_string(i));
  }
  EXPECT_TRUE(a == b);
}

TEST(operators_tests, isNotEqual_test_1) {
  HashTable a = HashTable(5);
  HashTable b = HashTable(5);

  a.insert("random", {1, 1});
  EXPECT_TRUE(a != b);
}

TEST(operators_tests, isNotEqual_test_2) {
  HashTable a = HashTable();
  HashTable b = HashTable();

  a.insert("KeyA", {1, 1});
  b.insert("KeyA", {2, 2});
  EXPECT_TRUE(a != b);
}

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
  Key key = "Key";
  Value value = {2, 2};
  a.insert(key, value);
  EXPECT_TRUE(a.contains("Key"));
}

TEST(methods_tests, insert_test_4) {
  HashTable a;
  int number = a.getCapacity() * 8;

  for (int i = 0; i < number; i++) {
    a.insert(std::to_string(i), {2, 2});
  }
  EXPECT_EQ(number, a.getSize()) << "size wasn't increased!!";
}

TEST(methods_tests, insert_test_5) {
  HashTable a;
  size_t number = a.getCapacity() * 8;

  for (size_t i = 0; i < number; i++) {
    a.insert("Key", {2, 2});
  }
  EXPECT_TRUE(number != a.getSize()) << "size was updated!!";
}

//
// TEST(methods_tests, insert_test_5) {
//   HashTable a;
//   auto number = SIZE_MAX;

//   for (int i = 0; i < number; i++) {
//     a.insert(std::to_string(i), {2, 2});
//   }
//   EXPECT_FALSE(a.insert("random", {}));
// }

TEST(methods_tests, rehashing_test_1) {
  HashTable a = HashTable(4);
  a.insert("Key", {1, 1});
  a.insert("Key1", {1, 2});
  a.insert("Key2", {5, 1});
  a.insert("Key3", {1, 9});
  EXPECT_EQ(8, a.getCapacity());
}

TEST(methods_tests, rehashing_test_2) {
  HashTable a;
  size_t init_capacity = a.getCapacity();
  int number = init_capacity * 8;

  for (int i = 0; i < number; i++) {
    a.insert(std::to_string(i), {2, 2});
  }
  EXPECT_TRUE(init_capacity != a.getCapacity()) << "size wasn't increased!!";
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
  HashTable a = HashTable();

  int number = 100;
  for (int i = 0; i <= number; i++){
    a.insert(std::to_string(i), {2, 2});
  }

  for (int i = 0; i <= number; i++){
    a.erase(std::to_string(i));
  }

  EXPECT_EQ(0, a.getSize());
}

// TEST(methods_tests, linear_probing_test_1) {
//   HashTable a = HashTable();
//   Key key = "testKey";
//   int result = a.linearProbing(0, key);
//   EXPECT_EQ(0, result);
// }

// TEST(methods_tests, linear_probing_test_2) {
//   HashTable a = HashTable();
//   Key key = "testKey";
//   Value value = {1, 1};
//   a.insert(key, value);

//   int startIndex = a.find(key);
//   int result = a.linearProbing(startIndex, key);
//   EXPECT_EQ(result, startIndex);
// }

// TEST(methods_tests, linear_probing_test_3) {
//   HashTable a = HashTable();

//   Key key1 = "testKey1";
//   Value value1 = {1, 1};
//   Key key2 = "testKey2";
//   Value value2 = {2, 2};

//   a.insert(key1, value1);
//   a.insert(key2, value2);

//   int startIndex = a.find(key1);
//   int result = a.linearProbing(startIndex, key2);
//   EXPECT_NE(result, startIndex);
// }

// TEST(methods_tests, linear_probing_test_4) {
//   HashTable a = HashTable();
//   for (int i = 0; i < a.getCapacity(); i++) {
//     Key key = "key" + std::to_string(i);
//     Value value = {1, 1};
//     a.insert(key, value);
//   }

//   // Now the table is full, so probing should not find a suitable index
//   Key newKey = "newKey";
//   int startIndex = 0;
//   int result = a.linearProbing(startIndex, newKey);
//   EXPECT_EQ(result, -1);
// }

// TEST(methods_tests, linear_probing_test_5) {
//   HashTable a = HashTable();

//   Key key1 = "key1";
//   Key key2 = "key2";
//   Key key3 = "key3";

//   a.insert(key1, {1, 1});
//   a.insert(key2, {1, 1});
//   a.insert(key3, {1, 1});

//   // Assuming a collision occurs, we want to find the next available slot
//   int startIndex = a.find(key1);
//   int result = a.linearProbing(startIndex, key2);
//   EXPECT_NE(result, startIndex);
// }

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
  EXPECT_NO_THROW({ a.clear(); });
}

TEST(methods_tests, clear_test_3) {
  HashTable a = HashTable(1);
  a.clear();
  EXPECT_TRUE(a.insert("rand", {}));
}

TEST(methods_tests, clear_test_4) {
  HashTable a(1);
  a.insert("0", {0,0});
  int number = 50;
  a.clear();
  for (int i = 1; i < number - 1; ++i) {
    EXPECT_TRUE(a.insert(std::to_string(i), {2, 2}));
  }
}

TEST(methods_tests, at_test_1) {
  HashTable a = HashTable();
  const Value value1 = {1, 1};
  const Value value2 = {2, 2};

  a.insert("1", value1);
  a.insert("2", value2);

  EXPECT_TRUE(a.at("1") == value1);
  EXPECT_TRUE(a.at("2") == value2);
}

TEST(methods_tests, at_test_2) {
  HashTable a = HashTable();
  const Value value1 = {1, 1};

  a.insert("1", value1);
  EXPECT_THROW(a.at("2"), std::runtime_error);
}

TEST(methods_tests, at_test_3) {
  HashTable a = HashTable();
  EXPECT_THROW(a.at("searching for nothing"), std::runtime_error);
}

TEST(methods_tests, swap_test_1) {
  HashTable a = HashTable();
  const Value value1 = {1, 1};
  a.insert("1", value1);
  HashTable b = HashTable();
  const Value value2 = {2, 2};
  b.insert("2", value2);
  b.insert("3", value2);

  a.swap(b);
  EXPECT_EQ(2, a.getSize());
  EXPECT_EQ(1, b.getSize());
  EXPECT_FALSE(a.contains("1"));
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
