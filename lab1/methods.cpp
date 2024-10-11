#include "hashtable.h"
#include <cstddef>
#include <stdexcept>

// magic 33 (hashing func for string key)
int HashTable::hash(const Key &key) const {
  unsigned long hash = 5381;

  for (auto c : key)
    hash = ((hash << 5) + hash) + c; // hash * 33 + c

  return hash % capacity;
}

double HashTable::getLoadFactor(double const &size, double const &capacity) {
  return size / capacity;
}

// if MAX_LOAD_FACTOR is exceeded double the size
// and rehash everything to the new table
void HashTable::rehashIfNeeded() {
  double load_factor =
      getLoadFactor(static_cast<double>(size), static_cast<double>(capacity));
  if (load_factor < MAX_LOAD_FACTOR)
    return;

  capacity *= 2;
  HashNode **newTable = new HashNode *[capacity]();
  for (int i = 0; i < capacity; i++)
    newTable[i] = new HashNode();

  for (int i = 0; i < capacity / 2; i++) {
    if (table[i] != nullptr) {
      int newIndex = hash(table[i]->key);
      if (newTable[newIndex] != nullptr) {
        delete newTable[newIndex]; // Free the existing node
      }
      newTable[newIndex] = std::move(table[i]);
    }
    table[i] = nullptr;
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

// collission resolution
// lineary go through table and search for empty/free or with the same key node
int HashTable::linearProbing(int startIndex, Key key) const {
  int i = startIndex;
  ++startIndex;
  while (i != startIndex) {
    if (table[i] == nullptr || table[i]->key.empty() || table[i]->key == key) {
      return i;
    }
    i = (i + 1) % capacity;
  }
  return -1; // Indicate that no suitable index was found (should not happen if
             // table is not full)
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

  // if node is empty or has the same key
  if (table[hashed_index] == nullptr || table[hashed_index]->key.empty() ||
      table[hashed_index]->key == k) {
    index = hashed_index;
  } else { // collission resolution
    index = linearProbing((hashed_index + 1) % capacity, k);
  }
  if (index != -1) {
    HashNode *newNode = new HashNode(k, v);
    table[index] = newNode;
    ++size;
    return true;
  }
  return false;
}

const Value &HashTable::at(const Key &k) const {
  int index = find(k);

  if (index == -1)
    throw std::runtime_error("Key not found: " + k);

  return table[index]->value;
}

Value &HashTable::at(const Key &k) {
  return const_cast<Value &>(static_cast<const HashTable *>(this)->at(k));
}

bool HashTable::contains(const Key &key) const { return (find(key) != -1); }

void HashTable::clear() {
  if (table == nullptr) {
    return;
  }

  for (size_t i = 0; i < capacity; ++i) {
    delete table[i];
    table[i] = nullptr;
  }
  size = 0;
}

size_t HashTable::getSize() const { return size; }
size_t HashTable::getCapacity() const { return capacity; }

bool HashTable::empty() const { return size == 0; }

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

void HashTable::swap(HashTable &other) {
  HashNode **otherT = other.table;
  other.table = table;
  table = otherT;

  std::swap(other.capacity, capacity);
  std::swap(other.size, size);
}
