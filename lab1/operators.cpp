#include "hashtable.h"

//copy assignment
//1) acquire new resources
//2) release old resources
//3) assign "new" resource values to the object
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

//move assignment
//1) deallocate current object's data
//2) copy other's data
//3) mark other data as nullptr
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
