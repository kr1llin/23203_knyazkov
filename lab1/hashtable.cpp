#include <cstddef>
#include <cstring>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

typedef std::string Key;

struct Value {
  unsigned age;
  unsigned weight;
};

class HashNode {
public:
  Value value;
  Key key;

  HashNode(Key key, Value value) {
    this->value = value;
    this->key = key;
  }
};

class HashTable {
private:
  HashNode **table;
  size_t capacity;
  size_t size;

  int hash(Key key) {
    int sum = 0;
    for (int i = 0; i < key.length(); i++)
      sum += int(key[i]);
    return sum % capacity;
  }

public:
  HashTable() : table(nullptr), capacity(0), size(0) {};
  ~HashTable() {
    for (size_t i = 0; i < capacity; ++i) {
      delete table[i];
    }
    delete[] table;
  }

  HashTable(size_t init_capacity) : capacity(init_capacity), size(0) {
    table = new HashNode *[capacity];
    for (int i = 0; i < capacity; i++)
      table[i] = nullptr;
  };

  HashTable(const HashTable &other) : capacity(other.capacity), size(other.size) {
    HashNode **newNode = new HashNode *[capacity];
    for (int i = 0; i < size; i++)
      newNode[i] = other.table[i];
  }

  HashTable(HashTable &&other) : capacity(((HashTable&&)other).capacity), size(((HashTable&&)other).size) {
    table = other.table;

    other.size = 0;
    other.capacity = 0;
    other.table = nullptr;
  } 

  void swap(HashTable &other){
    
  }


  // deep copy
  HashTable &operator=(const HashTable &other) {
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
  //
  HashTable &operator=(HashTable &&other) {
    if (this == &other) {
      return *this;
    }

    for (size_t i = 0; i < capacity; ++i) {
      delete table[i];
    }
    delete[] table;

    capacity = other.capacity;
    size = other.size;
    table = other.table;

    other.size = 0;
    other.capacity = 0;
    other.table = nullptr;

    return *this;
  }

  void clear();
  bool erase(const Key &k);
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

size_t HashTable::getSize() const { return size; }

bool HashTable::empty() const { return size == 0; }

// TODO: exception!
Value &HashTable::at(const Key &k) {
  int index = hash(k);
  if (table[index] == nullptr) {
    static Value dummy = {0, 0};
    return dummy;
  }
  return table[index]->value;
}

bool HashTable::contains(const Key &key) const { return at(key); }

// insertion using linear probing collision resolution
bool HashTable::insert(const Key &k, const Value &v) {
  if (size == capacity) {
    // overflow!
    return false;
  }

  HashNode *newNode = new HashNode(k, v);
  int index = hash(k);

  while (table[index] != nullptr && table[index]->key != k) {
    index = (index + 1) % capacity;
  }

  if (table[index] == nullptr)
    size++;
  table[index] = newNode;
  return true;
}

bool HashTable::erase(const Key &k) {
  int id = hash(k);
  delete table[id];
}

/*
void HashTable::handleCollission(Key key, Value value, size_t sizeTable){
    int index = hash(key);

    while(table[index] != NULL) {
        index = (index + 1) % sizeTable;
    }

    HashNode newNode(key, value);
    table[index] = &newNode;
}
*/
int main() { HashTable table(2); }
