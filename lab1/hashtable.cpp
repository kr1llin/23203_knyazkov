#include <cstddef>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

#define DEF_CAPACITY 10
#define MAX_LOAD_FACTOR 80

typedef std::string Key;

struct Value {
  unsigned age;
  unsigned weight;
};

struct HashNode {
  Value value;
  Key key;

  HashNode(Key key, Value value) {
    this->value = value;
    this->key = key;
  }

  // default = deleted\empty node
  HashNode() {
    this->key = "";
    this->value = {0, 0};
  }
};

class HashTable {
private:
  HashNode **table;
  size_t capacity;
  size_t size;
  // Empty node to use for deletion
  HashNode *dummy;

  int hash(const Key &key) const {
    int sum = 0;
    for (int i = 0; i < key.length(); i++)
      sum += int(key[i]);
    return sum % capacity;
  }

public:
  HashTable() : capacity(DEF_CAPACITY), size(0) {
    table = new HashNode *[capacity];
    for (int i = 0; i < capacity; i++)
      table[i] = nullptr;

    // Init deleted node (it's just empty)
    dummy = new HashNode();
  };

  ~HashTable() {
    for (size_t i = 0; i < capacity; ++i) {
      if (table[i] != nullptr && !table[i]->key.empty()) {
        delete table[i];
        table[i] = nullptr;
      }
    }
    free(dummy);
  }

  HashTable(size_t init_capacity);

  HashTable(const HashTable &other);

  HashTable(HashTable &&other);

  // std::swap uses move semantic
  // so it'll be expensive to copy and delete large amount of resources
  // Custom one is simple pointer exchange
  void swap(HashTable &other);

  // deep copy
  HashTable &operator=(const HashTable &other);

  HashTable &operator=(HashTable &&other);

  void rehashIfNeeded();
  // clears table and sets size to 0
  void clear();
  // Delete element by key
  // Returns true on success, false otherwise
  bool erase(const Key &k);
  // insertion using linear probing collision resolution
  bool insert(const Key &k, const Value &v);

  bool contains(const Key &k) const;

  Value &operator[](const Key &k);

  Value &at(const Key &k);
  const Value &at(const Key &k) const;

  size_t getSize() const;
  bool empty() const;

  friend bool operator==(const HashTable &a, const HashTable &b);
  friend bool operator!=(const HashTable &a, const HashTable &b);
};

HashTable::HashTable(const HashTable &other)
    : capacity(other.capacity), size(other.size) {
  HashNode **newNode = new HashNode *[capacity];
  for (int i = 0; i < size; i++)
    newNode[i] = other.table[i];

  dummy = new HashNode();
};

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

  dummy = new HashNode();
};

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
  if (this != &other) {

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
  return *this;
}
size_t HashTable::getSize() const { return size; }

bool HashTable::empty() const { return size == 0; }

Value &HashTable::at(const Key &k) {
  int index = hash(k);

  // Checks if hash index is free, if true - this is our target index
  for (int i = 0; ((table[index] == dummy) || (table[index]->key != k) ||
                   (!table[index]->key.empty()));
       i++) {
    index = (index + i) % capacity;
    if (i == capacity)
      throw std::runtime_error("Key is not found!");
  }

  return table[index]->value;
}

bool HashTable::contains(const Key &key) const {
  int index = hash(key);
  return (!(table[index] == dummy) && !(table[index] == nullptr));
}

void HashTable::clear() {
  for (size_t i = 0; i < capacity; ++i) {
    delete table[i];
  }
  delete[] table;

  size = 0;
}

// inserts node to container (return if it was success)
// otherwise, search for the first empty node (linear probing)
// rehash if needed (if container is almost full)
bool HashTable::insert(const Key &k, const Value &v) {
  if (size == capacity) {
    // overflow!
    return false;
  }

  int index = hash(k);
  for (int i = 0; ((table[index] != nullptr) &&(table[index] != dummy) && (table[index]->key != k) &&
                   (!table[index]->key.empty()));
       i++) {
    index = (index + i) % capacity;
    if (i == capacity){
      rehashIfNeeded();
      break;
    }
  }

  HashNode *newNode = new HashNode(k, v);
  size++;
  table[index] = newNode;
  rehashIfNeeded();

  return true;
}

// delete element by key k
// return if it was successuful (key is found and deleted)
bool HashTable::erase(const Key &k) {
  int index = hash(k);

  if (contains(k)) {
    delete table[index];
    table[index] = dummy;
    --size;
    return true;
  } else {
    return false;
  }
}

// if MAX_LOAD_FACTOR is exceeded double the size
// and rehash everything to the new table
void HashTable::rehashIfNeeded() {
  if (size / capacity <= MAX_LOAD_FACTOR) {
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
  int index = hash(k);

  for (int i = 0; ((table[index] == dummy) || (table[index]->key != k) ||
                   (!table[index]->key.empty()));
       i++) {
    index = (index + i) % capacity;
    if (i == capacity) {
      rehashIfNeeded();
      table[index] = new HashNode();
      return table[index]->value;
    }
  }
  return table[index]->value;
}

int main() {
  HashTable h(1);
  h.insert("Blah", {2,2});
  std::cout << h.getSize();
  h.insert("Blah", {2,2});
  h.at("Blah");
}
