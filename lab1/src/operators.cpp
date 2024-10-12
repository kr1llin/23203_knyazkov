#include "hashtable.h"
#include <iostream>
// copy assignment
// 1) acquire new resources
// 2) release old resources
// 3) assign "new" resource values to the object
HashTable &HashTable::operator=(const HashTable &other) {
  if (this == &other)
    return *this;

  // deallocating old resources

  for (size_t i = 0; i < capacity; i++) {
    if (table[i] != nullptr)
      delete table[i];
  }
  delete[] table;

  // copying data from other object
  capacity = other.capacity;
  size = other.size;

  table = new HashNode *[capacity];

  for (size_t i = 0; i < capacity; ++i) {
    if (other.table[i] != nullptr) {
      table[i] = new HashNode(*other.table[i]);
    } else {
      table[i] = nullptr;
    }
  }

  return *this;
}

// move assignment
// 1) deallocate current object's data
// 2) copy other's data
// 3) mark other data as nullptr
HashTable &HashTable::operator=(HashTable &&other) {
  if (this == &other) // sus
    return *this;

  for (size_t i = 0; i < capacity; ++i) {
    if (table[i] != nullptr)
      delete table[i];
  }
  delete[] table;

  table = other.table;
  size = other.size;
  capacity = other.capacity;

  other.table = nullptr;
  other.capacity = 0;
  other.size = 0;

  return *this;
}

// returns value by k key
Value &HashTable::operator[](const Key &k) {
  int index = find(k);

  if (index == -1) {
    HashNode empty = *new HashNode();
    this->insert(empty.key, empty.value);
    return table[find(empty.key)]->value;
  }
  return table[index]->value;
}

// comparassion between tables
bool operator==(const HashTable &a, const HashTable &b) {
  if (a.size != b.size) {
    return false;
  }

  for (size_t i = 0; i < a.capacity; i++) {
    if (a.table[i] != nullptr) {
      if (b.table[i] == nullptr || b.table[i]->key != a.table[i]->key ||
          b.table[i]->value != a.table[i]->value) {
        return false;
      }
    }
  }
  return true;
}

bool operator!=(const HashTable &a, const HashTable &b) { return !(a == b); }
