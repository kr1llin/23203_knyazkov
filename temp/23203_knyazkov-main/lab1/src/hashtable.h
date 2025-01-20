#pragma once

#include <string>

using Key = std::string;

struct Value {
  unsigned age;
  unsigned weight;

  bool operator==(const Value &b) const {
    return ((this->age == b.age) && (this->weight == b.weight));
  }

  bool operator!=(const Value &b) const { return !(*this == b); }
};

class HashTable {
public:
  HashTable();
  ~HashTable();

  explicit HashTable(size_t init_capacity);
  HashTable(const HashTable &other);
  HashTable(HashTable &&other);

  void swap(HashTable &other);

  HashTable &operator=(const HashTable &other);
  HashTable &operator=(HashTable &&other);

  void clear();
  bool erase(const Key &k);
  bool insert(const Key &k, const Value &v);

  bool contains(const Key &k) const;

  Value &operator[](const Key &k);

  Value &at(const Key &k);
  const Value &at(const Key &k) const;

  size_t getSize() const;
  size_t getCapacity() const;
  bool empty() const;

  friend bool operator==(const HashTable &a, const HashTable &b);
  friend bool operator!=(const HashTable &a, const HashTable &b);

private:
  static constexpr size_t DEF_CAPACITY = 10;
  static constexpr double MAX_LOAD_FACTOR = 0.6;
  static constexpr size_t CAPACITY_MULTIPLIER = 2;

  size_t capacity = 0;
  size_t size = 0;

  struct HashNode {
    Value value{};
    Key key;
    HashNode() = default;
    ~HashNode() = default;
    HashNode(Key key, Value value) : value(value), key(key) {};
    HashNode(const HashNode &other) = default;
    HashNode &operator=(const HashNode &other) = default;
    HashNode(HashNode &&other) = default;
    HashNode &operator=(HashNode &&other) = default;
  };

  enum class SearchType { SEARCH_FOR_NULLPTR, SEARCH_FOR_KEY };

  HashNode **table = nullptr;

  size_t hash(const Key &key) const;
  size_t linearProbing(size_t startIndex, Key const& key, SearchType searchT) const;
  void rehashIfNeeded();
  double getLoadFactor() const;
  size_t find(const Key &k) const;
  void deleteTable();
};
