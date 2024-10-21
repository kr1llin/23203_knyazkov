#include "hashtable.h"
#include <climits>
#include <stdexcept>

HashTable::HashTable() : capacity(DEF_CAPACITY), size(0) {
  table = new HashNode *[capacity];
  for (size_t i = 0; i < capacity; i++) {
    table[i] = new HashNode();
  }
};

HashTable::~HashTable() {
  for (size_t i = 0; i < capacity; i++) {
    if (table[i] != nullptr)
      delete table[i];
  }
  delete[] table;
};

HashTable::HashTable(const HashTable &other)
    : capacity(other.capacity), size(other.size) {
  table = new HashNode *[capacity];

  for (int i = 0; i < capacity; i++) {
    if (other.table[i] != nullptr) {
      table[i] = new HashNode(*other.table[i]);
    } else {
      table[i] = new HashNode(); // empty node
    }
  }
};

HashTable::HashTable(size_t init_capacity) : size(0) {
  if (init_capacity == 0) {
    throw std::invalid_argument("WHY ARE YOU DOING THIS?");
  }
  capacity = init_capacity;
  table = new HashNode *[capacity];
  for (int i = 0; i < capacity; i++)
    table[i] = new HashNode();
};

HashTable::HashTable(HashTable &&other)
    : capacity((other.capacity)), size(other.size) {
  table = other.table;
  size = other.size;
  capacity = other.capacity;

  other.table = nullptr;
  other.capacity = 0;
  other.size = 0;
};
