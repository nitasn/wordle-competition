#include "known_words.h"
#include <iostream>
#include <cassert>

int main() {
  std::cout << knownWords.size() << '\n';

  Word word = std::string("hello");
  word[1] = 'y';
  for (int i = 0; i < 5; i++) {
    assert(word[i] == "hyllo"[i]);
  }
}