#include "../src/hashtable.h"
#include <gtest/gtest.h>

// memory/address sanitizer
// clang-tidy

//const-cast (для at())

// for memory allocation errors - try catch bad_alloc

// dont forget about private methods (use friend)

// test copy\move construction

// git_ignore this

// think evil

// check coverage in the end

// ASSERT_* generate fatal failures when they fail. And abort the current func
// EXPECT_* generate nonfatal failures, which don't abort current function

// память запрещённым способом.  <<<<<<<<<<< НАПИШИ ТЕСТ ВЫИСКИВАЮЩИЙ ЗАПРЕЩЁННУЮ ЗАПИСЬ\ОБРАЩЕНИЕ!!!

/*
TEST(HashTable, isEmptyTest) {

  ///
  HashTable ht;

  ht.insert("abc", {1, 2});
  ht.erase("abc");
  EXPECT_TRUE(ht.empty());

  ///
};

TEST(HashTable, copyCtor){
  //IS TABLE REALLY BECOME NEW TABLE

  //
}

TEST(HashTable, moveCtor){

}

TEST(HashTable, rehashIfNeeded){
  //EXPECT: CURSIZE = OLDSIZE * 2

  //NEW TABLE != nullptr or catche bad_alloc

  //TEST IF OLD TABLE IN NEWTABLE (ALL IT'S ELEMENTS)

  //CHECK IF OLD TABLE IS REALLY DESTROYED 
}

TEST(HashTable, find){
  //insert -> find -> EXPECT NOT -1

  //CHECK FOR EMPTY NODE (when key is "")

  //CHECK FOR NOT EMPTY NODE
}

TEST(HashTable, InsertTest) {
  // same object 10 times
  // insert and check if size've incremented
}
*/

int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
