#include "../../src/hashtable.cpp"
#include <iostream>

int main(){
    HashTable table = HashTable();
    HashTable b = HashTable();
    HashTable c(b);
    std::clog << "JUST IN CASE!";
    return 0;
}
