#ifndef WORD_H
#define WORD_H

#include <cstdint>
#include <string>
#include <cassert>

class Word {
private:
  uint64_t bits;

public:
  Word(const std::string &str);
  Word(const char* str);
  char operator[](int i) const;
  char& operator[](int i);
  bool operator==(const Word word) const;
};

#endif // WORD_H
