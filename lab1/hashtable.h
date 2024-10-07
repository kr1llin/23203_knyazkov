#pragma once

#include <cstddef>
#include <cstring>
#include <exception>
#include <iostream>
#include <string>

static constexpr size_t DEF_CAPACITY = 10;
static constexpr double MAX_LOAD_FACTOR = 0.8l;

typedef std::string Key;

struct Value {
  unsigned age;
  unsigned weight;

  bool operator==(const Value &b){
    return ((this->age == b.age) && (this->weight == b.weight));
  }
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
  int hash(const Key &key) const;

public:
  HashTable();
  ~HashTable();

  //constructor by capacity
  HashTable(size_t init_capacity);
  //copy contructor
  HashTable(const HashTable &other);
  //move constructor
  HashTable(HashTable &&other);

  void swap(HashTable &other);

  // deep copy
  HashTable &operator=(const HashTable &other);

  HashTable &operator=(HashTable &&other);

  void rehashIfNeeded();
  //find index in hastable by key
  int find(const Key &k) const;
  
  void clear();
  // Delete element by key
  // Returns true on success, false otherwise
  bool erase(const Key &k);
  // insertion using linear probing collision resolution
  bool insert(const Key &k, const Value &v);

  bool contains(const Key &k) const;

  Value &operator[](const Key &k) const;

  Value &at(const Key &k);
  const Value &at(const Key &k) const;

  size_t getSize() const;
  size_t getCapacity() const;
  bool empty() const;

  friend bool operator==(const HashTable &a, const HashTable &b);
  friend bool operator!=(const HashTable &a, const HashTable &b);
};
