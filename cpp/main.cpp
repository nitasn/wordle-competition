#include "known_words.h"
#include <iostream>

int main() {
  std::cout << knownWords.size() << '\n';

  Word word = "hello";
  word[1] = 'y';
  for (int i = 0; i < 5; i++) {
    assert(word[i] == "hyllo"[i]);
  }
}