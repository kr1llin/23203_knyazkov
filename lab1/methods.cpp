#include "hashtable.h"
#include <cstddef>

//magic 33
int HashTable::hash(const Key &key) const {
  unsigned long hash = 5381;

  for (auto c : key)
    hash = ((hash << 5) + hash) + c; // hash * 33 + c

  return hash % capacity;
}

// if MAX_LOAD_FACTOR is exceeded double the size
// and rehash everything to the new table
void HashTable::rehashIfNeeded() {
  double load_factor =
      static_cast<double>(size) / static_cast<double>(capacity);
  if (load_factor < MAX_LOAD_FACTOR)
    return;

  capacity *= 2;
  HashNode **newTable = new HashNode *[capacity];

  for (int i = 0; i < capacity; i++)
    newTable[i] = new HashNode();

  for (int i = 0; i < capacity / 2; i++) {
    if (table[i] != nullptr) {
      newTable[hash(table[i]->key)] = table[i];
      delete table[i];
    }
  }
  delete[] table;
  table = newTable;
}

// delete element by key k
// return if it was successuful (key is found and deleted)
bool HashTable::erase(const Key &k) {
  int hashed_index = hash(k);
  int index = -1;
  if (table[hashed_index]->key == k) {
    index = hashed_index;
  } else {
    index = find(k);
  }

  if (index == -1)
    return false;

  delete table[index];
  HashNode *empty = new HashNode();
  table[index] = empty;
  size--;
  return true;
}

// insertion using linear probing collision resolution
// inserts node to container (return if it was success)
// otherwise, search for the first empty node (linear probing)
bool HashTable::insert(const Key &k, const Value &v) {
  rehashIfNeeded();
  if (size == capacity) {
    return false;
  }
  int index = -1;
  int hashed_index = hash(k);

  //if node is empty or has the same key
  if (table[hashed_index] == nullptr || table[hashed_index]->key.empty() ||
      table[hashed_index]->key == k) {
    index = hashed_index;
  } else { //or search circularly for empty / with same key node
    int i = (hashed_index + 1) % capacity;
    while (i != hashed_index) {
      if (table[i] == nullptr || table[i]->key.empty() || table[i]->key == k) {
        index = i;
        break;
      }
      i = (i + 1) % capacity;
    }
  }

  HashNode *newNode = new HashNode(k, v);
  table[index] = newNode;
  ++size;

  return (index != -1);
}

Value &HashTable::at(const Key &k) {
  int index = hash(k);
  //index = find(k);
  if (index == -1)
    throw std::runtime_error("Key" + k + "is not found!");

  return table[index]->value;
}

bool HashTable::contains(const Key &key) const { return (find(key) != -1); }

// clears table and sets size to 0
void HashTable::clear() {
  for (size_t i = 0; i < capacity; ++i) {
    delete table[i];
    table[i] = nullptr;
  }
  size = 0;
}

size_t HashTable::getSize() const { return size; }
size_t HashTable::getCapacity() const { return capacity; }

bool HashTable::empty() const { return size == 0; }

//find node by k key
int HashTable::find(const Key &k) const {
  int index = hash(k);

  if (table[index]->key == k)
    return index;

  if (table[index] == nullptr)
    return -1;

  int i = (index + 1) % capacity;
  while (i != index && table[i] != nullptr) {
    if (table[i]->key == k) {
      return i;
    }
    i = (i + 1) % capacity;
  }

  return -1;
}

// std::swap uses move semantic
// so it'll be expensive to copy and delete large amount of resources
// Custom one is simple pointer exchange
void HashTable::swap(HashTable &other) {
  HashNode **otherT = other.table;
  other.table = table;
  table = otherT;

  std::swap(other.capacity, capacity);
  std::swap(other.size, size);
}

