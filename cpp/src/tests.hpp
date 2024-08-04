#include "known_words.h"
#include <iostream>
#include <cassert>
#include <string>

void testWord() {
  Word word = std::string("hello");
  word[1] = 'y';
  const Word constWord = word;
  for (int i = 0; i < 5; i++) {
    assert(constWord[i] == "hyllo"[i]);
  }
}