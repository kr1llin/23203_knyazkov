#include "hashtable.h"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <stdexcept>

// magic 33 (hashing func for string key)
size_t HashTable::hash(const Key &key) const {
  unsigned long hash = 5381;

  for (auto c : key)
    hash = ((hash << 5) + hash) + c; // hash * 33 + c

  return hash % capacity;
}

double HashTable::getLoadFactor() const {
  return static_cast<double>(size) / capacity;
}

// if MAX_LOAD_FACTOR is exceeded double the size
// and rehash everything to the new table
void HashTable::rehashIfNeeded() {
  double load_factor = getLoadFactor();
  if (load_factor < MAX_LOAD_FACTOR)
    return;

  capacity *= CAPACITY_MULTIPLIER;

  HashTable newTable = HashTable(capacity);

  for (int i = 0; i < capacity / 2; i++) {
    newTable.insert(table[i]->key, table[i]->value);
    erase(table[i]->key);
    table[i] = nullptr;
  }
  delete[] table;
  table = newTable.table;
}

// delete element by key k
// return if it was successuful (key is found and deleted)
bool HashTable::erase(const Key &k) {
  size_t hashed_index = hash(k);
  size_t index = capacity; //out of range

  if (table[hashed_index]->key == k) {
    index = hashed_index;
  } else {
    index = find(k);
  }

  if (index == capacity)
    return false;

  // *table[index] = HashNode(); //if we want to place default value
  delete table[index];
  table[index] = nullptr; //node is deleted = nullptr
  size--;
  return true;
}

// collission resolution
// lineary go through table and search for empty/free or with the same key node
//index = capacity => index wasn't found
size_t HashTable::linearProbing(int startIndex, Key key) const {
  size_t curIndex = startIndex;

  for(size_t i = 0; i != capacity; i++){
    curIndex = (curIndex + i) % capacity;
    if (table[curIndex] == nullptr || table[curIndex]->key == key) {
      return curIndex;
    }
  }
  return capacity; // Indicate that no suitable index was found (returns value outside of range)
}

// insertion using linear probing collision resolution
// inserts node to container (return if it was success)
// otherwise, search for the first empty node (linear probing)
bool HashTable::insert(const Key &k, const Value &v) {
  rehashIfNeeded();

  size_t index = capacity;
  size_t hashed_index = hash(k);

  // if node is empty or has the same key
  if (table[hashed_index] == nullptr || table[hashed_index]->key == k) {
    index = hashed_index;
  } else { // collission resolution
    index = linearProbing(hashed_index, k);
  }
  
  if (index != capacity) {
    *table[index] = HashNode(k,v);
    ++size;
    return true;
  }
  return false;
}

const Value &HashTable::at(const Key &k) const {
  size_t index = find(k);
  if (index == capacity)
    throw std::runtime_error("Key not found: " + k);

  return table[index]->value;
}

Value &HashTable::at(const Key &k) {
  return const_cast<Value &>(static_cast<const HashTable *>(this)->at(k));
}

bool HashTable::contains(const Key &key) const { return (find(key) != -1); }

void HashTable::clear() {
  for (size_t i = 0; i < capacity; ++i) {
    if (table[i] != nullptr){
      delete table[i];
      table[i] = nullptr;
    }
  }
  size = 0;
}

size_t HashTable::getSize() const { return size; }
size_t HashTable::getCapacity() const { return capacity; }

bool HashTable::empty() const { return size == 0; }

size_t HashTable::find(const Key &k) const {
  size_t index = hash(k);

  if (table[index]->key == k)
    return index;

  if (table[index] == nullptr)
    return capacity;
  
  size_t i = (index + 1) % capacity;
  while (i != index && table[i] != nullptr) {
    if (table[i]->key == k) {
      return i;
    }
    i = (i + 1) % capacity;
  }
  return capacity;
}

void HashTable::swap(HashTable &other) {
  std::swap(other.table, table);
  std::swap(other.capacity, capacity);
  std::swap(other.size, size);
}
