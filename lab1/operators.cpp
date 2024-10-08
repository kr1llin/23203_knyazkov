#include "hashtable.h"

//copy assignment
HashTable &HashTable::operator=(const HashTable &other) {
  if (this == &other)
    return *this;

  for (size_t i = 0; i < capacity; ++i) {
    delete table[i];
  }
  delete[] table;

  capacity = other.capacity;
  size = other.size;
  table = new HashNode *[capacity];
  for (size_t i = 0; i < capacity; ++i) {
    table[i] = other.table[i];
  }
  return *this;
}

//move assignment
HashTable &HashTable::operator=(HashTable &&other) {
  if (this == &other) // sus
    return *this;

  for (size_t i = 0; i < capacity; ++i) {
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

//returns value by k key
Value &HashTable::operator[](const Key &k) const {
  int index = find(k);
  if (index == -1) {
    index = find("");
  }
  return table[index]->value;
}

//comparassion between tables
bool operator==(const HashTable &a, const HashTable &b) {
  int isEq = true;

  for (size_t i = 0; i < a.capacity; i++) {
    Key k = a.table[i]->key;
    if (!(b[k] == a[k])) {
      isEq = false;
      break;
    }
  }
  return isEq;
}

bool operator!=(const HashTable &a, const HashTable &b) { return !(a == b); }
