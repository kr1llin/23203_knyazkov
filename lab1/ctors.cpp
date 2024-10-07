#include "hashtable.h"
#include <climits>
#include <cstdint>
#include <stdexcept>

HashTable::HashTable() : capacity(DEF_CAPACITY), size(0) {
  table = new HashNode *[capacity];
  for (int i = 0; i < capacity; i++)
    table[i] = new HashNode();
};

HashTable::~HashTable() {
  for (size_t i = 0; i < capacity; ++i) {
    if (table[i] != nullptr) {
      delete table[i];
    }
  }
  delete[] table;
};

HashTable::HashTable(const HashTable &other)
    : capacity(other.capacity), size(other.size) {
  HashNode **newNode = new HashNode *[capacity];
  for (int i = 0; i < size; i++)
    newNode[i] = other.table[i];
};

// empty table (all nodes = nullptr)
HashTable::HashTable(size_t init_capacity) : size(0) {
  if (init_capacity > SIZE_MAX){
    throw std::out_of_range("CAPACITY IS OUT OF LONG RANGE");
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
