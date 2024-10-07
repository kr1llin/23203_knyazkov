#include "hashtable.h"

int main(int argc, char *argv[]) {
  HashTable h(1);
  h.insert("Blah", {2, 2});
  std::cout << h.getSize();
  h.insert("Blah", {2, 2});
  h.at("Blah");

  HashTable a(h);
  bool iseq = h == a;

  std::cout << iseq;

  //::testing::InitGoogleTest(&argc, argv);
  //return RUN_ALL_TESTS();
}
