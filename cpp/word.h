#ifndef WORD_H
#define WORD_H

#include <string>

class Word {
private:
  uint64_t bits;
  inline constexpr Word(uint64_t bits) : bits(bits) {}

public:
  Word(const std::string &str);
  char operator[](int i) const;
  char& operator[](int i);
  bool operator==(const Word word) const;
  int indexOf(char ch) const;
  
  static constexpr Word filledWith(char letter) {
    uint64_t bits = 0;
    for (size_t i = 0; i < 5; ++i) {
      bits |= static_cast<uint64_t>(letter) << (i * 8);
    }
    return Word(bits);
  }
};

#endif // WORD_H
