#include "hashtable.h"
#include <cstddef>

int HashTable::hash(const Key &key) const {
  int sum = 0;
  for (int i = 0; i < key.length(); i++)
    sum += int(key[i]);
  return sum % capacity;
}

// if MAX_LOAD_FACTOR is exceeded double the size
// and rehash everything to the new table
void HashTable::rehashIfNeeded() {
  double load_factor = static_cast<double>(size) / static_cast<double>(capacity);
  //std::clog << "LOAD FACTORRR = " << load_factor << std::endl;
  if (load_factor < MAX_LOAD_FACTOR)
    return;

  capacity *= 2;
  HashNode **newTable = new HashNode *[capacity];

  for (int i = 0; i < capacity; i++)
    newTable[i] = new HashNode();

  for (int i = 0; i < capacity / 2; i++) {
    if (table[i] != nullptr){
      newTable[hash(table[i]->key)] = table[i];
    }
  }
  delete[] table;
  table = newTable;
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
  } 
  return false;
}

// inserts node to container (return if it was success)
// otherwise, search for the first empty node (linear probing)
// rehash if needed (if container is almost full)
bool HashTable::insert(const Key &k, const Value &v) {
  if (size == capacity){
    rehashIfNeeded();
    return false;
  }
  
  int index = find(k);
  Value empty = Value();
  rehashIfNeeded();

  if (index == -1 || table[index]->key.empty() || table[index] == nullptr) {
    int index = hash(k);
    HashNode *newNode = new HashNode(k, v);
    size++;
    table[index] = newNode;
  } else {
    table[index]->value = v;
  }
  return true;
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

size_t HashTable::getSize() const { return size; }
size_t HashTable::getCapacity() const {return capacity;}

bool HashTable::empty() const { return size == 0; }

// linear search
//-1 if not found
int HashTable::find(const Key &k) const {
  int index = hash(k);
  for (int i = 0; ((table[index] == nullptr) && (table[index]->key != k) &&
                   (table[index]->key.empty()));
       i++) {

    index = (index + i) % capacity;
    if (i == capacity) {
      index = -1;
      break;
    }
  }
  return index;
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
