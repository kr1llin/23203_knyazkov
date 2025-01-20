#include "hashtable.h"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <stdexcept>

/*--------CONSTRUCTORS---------*/

HashTable::HashTable()
    : capacity(DEF_CAPACITY), table(new HashNode *[capacity]) {
  std::fill(table, table + capacity, nullptr);
};

HashTable::~HashTable() {
  if (table != nullptr) {
    deleteTable();
  }
};

HashTable::HashTable(const HashTable &other)
    : capacity(other.capacity), size(other.size),
      table(new HashNode *[capacity]) {
  std::transform(
      other.table, other.table + capacity, table,
      [](HashNode *node) { return node ? new HashNode(*node) : nullptr; });
};

HashTable::HashTable(size_t init_capacity) {
  if (init_capacity == 0) {
    throw std::invalid_argument("nope");
  }
  capacity = init_capacity;
  table = new HashNode *[capacity];
  std::fill(table, table + capacity, nullptr);
};

HashTable::HashTable(HashTable &&other)
    : capacity(other.capacity), size(other.size), table(other.table) {
  other.table = nullptr;
  other.capacity = 0;
  other.size = 0;
};

/*--------METHODS---------*/

// // magic 33 (hashing func for string key)
// size_t HashTable::hash(const Key &key) const {
//   uint64_t hash = 5381;

//   for (auto c : key){
//     hash = ((hash << 5) + hash) + c; // hash * 33 + c
//   }

//   return hash % capacity;
// }

size_t HashTable::hash(const Key &key) const { return 1 % capacity; }

double HashTable::getLoadFactor() const {
  return static_cast<double>(size) / (capacity);
}

void HashTable::deleteTable() {
  for (size_t i = 0; i < capacity; i++) {
    if (table[i] != nullptr) {
      delete table[i];
    }
  }
  delete[] table;
}

// if MAX_LOAD_FACTOR is exceeded double the size
// and rehash everything to the new table
void HashTable::rehashIfNeeded() {
  const double load_factor = getLoadFactor();
  if ((load_factor < MAX_LOAD_FACTOR) ||
      (capacity >= SIZE_MAX / CAPACITY_MULTIPLIER)) {
    return;
  }
  const size_t old_capacity = capacity;
  capacity *= CAPACITY_MULTIPLIER;
  HashTable newTable(capacity);

  for (size_t i = 0; i < old_capacity; i++) {
    if (table[i] != nullptr) {
      newTable.insert(table[i]->key, table[i]->value);
      delete table[i];
      table[i] = nullptr;
    }
  }
  delete[] table;
  table = nullptr;
  std::swap(table, newTable.table);
}

size_t HashTable::find(const Key &k) const {
  size_t hashed_index = hash(k);
  size_t index = hashed_index;

  if (table[hashed_index] != nullptr && table[hashed_index]->key == k) {
    return index;
  } else {
    index = linearProbing(index, k, SearchType::SEARCH_FOR_KEY);
  }
  return index;
}

// delete element by key k
// return if it was successuful (key is found and deleted)
bool HashTable::erase(const Key &k) {
  const size_t index = find(k);
  if (index == capacity) {
    return false;
  }
  std::clog << "> deleting " << k << std::endl;

  delete table[index];
  table[index] = nullptr; // node is deleted = nullptr
  size--;
  return true;
}

// collission resolution:
// lineary go through table and search for empty/free or with the same key node
// index = capacity => index wasn't found (no bucket with key or buckets are
// full)
size_t HashTable::linearProbing(size_t startIndex, Key const &key, SearchType searchT) const {
  size_t curIndex = startIndex;

  for (size_t i = 0; i <= capacity; i++) {
    if ((searchT == SearchType::SEARCH_FOR_NULLPTR && table[curIndex] == nullptr) ||
        (searchT == SearchType::SEARCH_FOR_KEY && table[curIndex] != nullptr &&
         table[curIndex]->key == key)) {
      return curIndex; // Return the current index if the condition is met
    }
    curIndex = (curIndex + i) % capacity;
  }
  return capacity;
}

// insertion using linear probing collision resolution
// inserts node to container (return if it was success)
// otherwise, search for the first empty node (linear probing)
bool HashTable::insert(const Key &k, const Value &v) {
  rehashIfNeeded();
  size_t index = hash(k);
  // if node is not empty or doesn't have the same key
  if (!(table[index] == nullptr) && !(table[index]->key == k)) {
    index = linearProbing(index, k, SearchType::SEARCH_FOR_NULLPTR); // collission resolution
  }
  // if index was found
  if (index != capacity) {
    if (table[index] == nullptr) {
      table[index] = new HashNode(k, v);
      ++size;
      return true;
    }
  }
  return false;
}

const Value &HashTable::at(const Key &k) const {
  const size_t index = find(k);
  if (index == capacity) {
    throw std::runtime_error("Key not found: " + k);
  }
  return table[index]->value;
}

Value &HashTable::at(const Key &k) {
  return const_cast<Value &>(static_cast<const HashTable *>(this)->at(k));
}

bool HashTable::contains(const Key &key) const {
  return (find(key) != capacity);
}

void HashTable::clear() {
  deleteTable();
  table = new HashNode *[capacity];
  std::fill(table, table + capacity, nullptr);
  size = 0;
}

size_t HashTable::getSize() const { return size; }
size_t HashTable::getCapacity() const { return capacity; }
bool HashTable::empty() const { return size == 0; }

void HashTable::swap(HashTable &other) {
  std::swap(other.table, table);
  std::swap(other.capacity, capacity);
  std::swap(other.size, size);
}

/*--------OPERATORS---------*/

// copy assignment
// 1) acquire new resources
// 2) release old resources
// 3) assign "new" resource values to the object
HashTable &HashTable::operator=(const HashTable &other) {
  if (this == &other) {
    return *this;
  }

  // deallocating old resources
  deleteTable();

  // copying data from other object
  capacity = other.capacity;
  size = other.size;
  table = new HashNode *[capacity];

  std::transform(other.table, other.table + capacity, table,
                 [](const HashNode *node) {
                   return node != nullptr ? new HashNode(*node) : nullptr;
                 });
  return *this;
}

// move assignment
// 1) deallocate current object's data
// 2) copy other's data
// 3) mark other data as nullptr
HashTable &HashTable::operator=(HashTable &&other) {
  if (this == &other) {
    return *this;
  }

  deleteTable();

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
  const size_t hashed_index = hash(k);
  const size_t index = linearProbing(hashed_index, k, SearchType::SEARCH_FOR_KEY);

  if (table[index] != nullptr && table[index]->key == k) {
    return table[index]->value;
  }

  table[index] = new HashNode();
  this->insert(table[index]->key, table[index]->value);

  return table[index]->value;
}

// comparison between tables
bool operator==(const HashTable &a, const HashTable &b) {
  if (a.size != b.size) {
    return false;
  }
  for (size_t i = 0; i < a.capacity; i++) {
    if (a.table[i] != nullptr) {
      HashTable::HashNode *curNode = a.table[i];
      // no node with this key or has diff value
      if (!b.contains(curNode->key) || b.at(curNode->key) != curNode->value) {
        return false;
      }
    }
  }
  return true;
}

bool operator!=(const HashTable &a, const HashTable &b) { return !(a == b); }
