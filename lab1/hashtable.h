#pragma once

#include <cstddef>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

static constexpr size_t DEF_CAPACITY = 10;
static constexpr size_t MAX_LOAD_FACTOR = 80;

typedef std::string Key;

struct Value {
  unsigned age;
  unsigned weight;
};

struct HashNode {
  Value value;
  Key key;

  HashNode(Key key, Value value) {
    this->value = value;
    this->key = key;
  }

  // default = deleted\empty node
  HashNode() {
    this->key = "";
    this->value = {0, 0};
  }
};

class HashTable {
private:
  HashNode **table;
  size_t capacity;
  size_t size;
  // Empty node to use for deletion
  HashNode *dummy;

  int hash(const Key &key) const {
    int sum = 0;
    for (int i = 0; i < key.length(); i++)
      sum += int(key[i]);
    return sum % capacity;
  }

public:
  HashTable();
  ~HashTable();

  HashTable(size_t init_capacity);
  HashTable(const HashTable &other);
  HashTable(HashTable &&other);

  // std::swap uses move semantic
  // so it'll be expensive to copy and delete large amount of resources
  // Custom one is simple pointer exchange
  void swap(HashTable &other);

  // deep copy
  HashTable &operator=(const HashTable &other);

  HashTable &operator=(HashTable &&other);

  void rehashIfNeeded();
  // clears table and sets size to 0
  void clear();
  // Delete element by key
  // Returns true on success, false otherwise
  bool erase(const Key &k);
  // insertion using linear probing collision resolution
  bool insert(const Key &k, const Value &v);

  bool contains(const Key &k) const;

  Value &operator[](const Key &k);

  Value &at(const Key &k);
  const Value &at(const Key &k) const;

  size_t getSize() const;
  bool empty() const;

  friend bool operator==(const HashTable &a, const HashTable &b);
  friend bool operator!=(const HashTable &a, const HashTable &b);
};
