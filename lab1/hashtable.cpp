#include "hashtable.h"
#include <stdexcept>

HashTable::HashTable() : capacity(DEF_CAPACITY), size(0) {
  table = new HashNode *[capacity];
  for (int i = 0; i < capacity; i++)
    table[i] = nullptr;

  // Init deleted node (it's just empty)
  // dummy = new HashNode();
};

HashTable::~HashTable() {
  for (size_t i = 0; i < capacity; ++i) {
    if (table[i] != nullptr) {
      delete table[i];
    }
  }
  delete[] table;
  // free(dummy);
};

HashTable::HashTable(const HashTable &other)
    : capacity(other.capacity), size(other.size) {
  HashNode **newNode = new HashNode *[capacity];
  for (int i = 0; i < size; i++)
    newNode[i] = other.table[i];

  // dummy = new HashNode();
};

// empty table (all nodes = nullptr)
HashTable::HashTable(size_t init_capacity) : capacity(init_capacity), size(0) {
  table = new HashNode *[capacity];
  for (int i = 0; i < capacity; i++)
    table[i] = nullptr;

  // Init deleted node (it's just empty)
  dummy = new HashNode();
};

HashTable::HashTable(HashTable &&other)
    : capacity((other.capacity)), size(other.size) {
  table = other.table;
  size = other.size;
  capacity = other.capacity;

  other.table = nullptr;
  other.capacity = 0;
  other.size = 0;

  // dummy = new HashNode();
};

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

HashTable &HashTable::operator=(HashTable &&other) {
  if (this != &other) // sus
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
}
size_t HashTable::getSize() const { return size; }

bool HashTable::empty() const { return size == 0; }

// linear search
//-1 if not found
int HashTable::find(const Key &k) const {
  int index = hash(k);
  if (k.empty()) {
    for (int i = 0; ((table[index] != nullptr) && !(table[index]->key.empty()));
         i++) {
      index = (index + i) % capacity;
      if (i == capacity) {
        index = -1;
        break;
      }
    }
  } else {
    for (int i = 0; ((table[index] == nullptr) || (table[index]->key != k) ||
                     (table[index]->key.empty()));
         i++) {
      index = (index + i) % capacity;
      // there're for sure no element with k key
      if (i == capacity) {
        index = -1;
        break;
      }
    }
  }

  return index;
}

Value &HashTable::at(const Key &k) {
  int index = hash(k);

  // Checks if hash index is free, if true - this is our target index
  // for (int i = 0; ((table[index] == dummy) || (table[index]->key != k)); i++)
  // {
  index = find(k);
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

// inserts node to container (return if it was success)
// otherwise, search for the first empty node (linear probing)
// rehash if needed (if container is almost full)
bool HashTable::insert(const Key &k, const Value &v) {
  if (size == capacity)
    return false;
  
  rehashIfNeeded();
  int index = find("");
  if (index == -1)
    return false;

  HashNode *newNode = new HashNode(k, v);
  size++;
  table[index] = newNode;
  return true;
}

// delete element by key k
// return if it was successuful (key is found and deleted)
bool HashTable::erase(const Key &k) {
  int index = hash(k);

  if (contains(k)) {
    delete table[index];
    table[index] = nullptr;
    --size;
    return true;
  } else {
    return false;
  }
}

// if MAX_LOAD_FACTOR is exceeded double the size
// and rehash everything to the new table
void HashTable::rehashIfNeeded() {
  if ((size / capacity) * 100 <= MAX_LOAD_FACTOR) {
    return;
  }
  capacity *= 2;
  HashNode **newTable = new HashNode *[capacity];

  for (int i = 0; i < capacity / 2; i++) {
    newTable[i] = table[i];
  }
  delete[] table;
  table = newTable;
}

Value &HashTable::operator[](const Key &k) {
  int index = find(k);
  if (index == -1){
    Value* empty = new Value();
    return *empty;
  }
  return table[index]->value;
}

int HashTable::hash(const Key &key) const {
  int sum = 0;
  for (int i = 0; i < key.length(); i++)
    sum += int(key[i]);
  return sum % capacity;
}

bool operator==(const HashTable &a, const HashTable &b) {
  int isEq = true;

  for (size_t i = 0; i < a.capacity; i++) {
    Key k = a.table[i]->key;
    if ((b[k].age != a[k].age) && (b[k].weight != a[k].weight)) {
      isEq = false;
      break;
    }
  }
  return isEq;
}

bool operator!=(const HashTable &a, const HashTable &b) { return !(a == b); }
