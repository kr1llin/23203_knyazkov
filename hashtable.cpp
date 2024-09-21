#include <cstddef>
#include <cstring>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

typedef std::string Key;

struct Value{
    unsigned age;
    unsigned weight;
};

class HashNode {
    public:
        Value value;
        Key key;
    
    HashNode(Key key, Value value)
    {
        this->value = value;
        this->key = key;
    }
};

class HashTable{
    private:
        HashNode** table;
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
            table = new HashNode*[capacity];
            for (int i = 0; i < capacity; i++)
                table[i] = nullptr;
        };

        HashTable(const HashTable& b);
        HashTable(HashTable&& b);

        void swap(HashTable& b);

        HashTable& operator=(const HashTable& b);
        HashTable& operator=(HashTable&& b);

        void clear();
        bool erase(const Key& k);
        bool insert(const Key& k, const Value& v);

        bool contains(const Key& k) const;

        Value& operator[](const Key& k);

        Value& at(const Key& k);
        const Value& at(const Key& k) const;

        size_t getSize() const;
        bool empty() const;

        friend bool operator==(const HashTable& a, const HashTable& b);
        friend bool operator!=(const HashTable& a, const HashTable& b);
};

size_t HashTable::getSize() const{
    return size;
}

bool HashTable::empty() const{
    return size == 0;
}

//TODO: exception!
Value& HashTable::at(const Key& k){
    int index = hash(k);
    if (table[index] == nullptr){
        static Value dummy = {0,0};
        return dummy;
        }
    return table[index]->value;
}

bool HashTable::contains(const Key& key) const{
    return at(key);
}

//insertion using linear probing collision resolution
bool HashTable::insert(const Key& k, const Value& v){
    if (size == capacity) {
        //overflow!
        return false;
    }

    HashNode* newNode = new HashNode(k, v);
    int index = hash(k);

    while(table[index] != nullptr && table[index]->key != k){
        index = (index + 1) % capacity;
    }

    if (table[index] == nullptr) size++;
    table[index] = newNode;
    return true;
}

Value& HashTable::operator[](const Key& k){
    if (!contains(k))
        //RETURN VALUE MADE BY DEFAULT CONSTRUCTOR
}

bool HashTable::erase(const Key& k){
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
int main(){
    HashTable table(2);
}
