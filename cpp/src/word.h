#ifndef WORD_H
#define WORD_H

#include <string>

class Word {
private:
  uint64_t bits;
  inline constexpr Word(uint64_t bits) : bits(bits) {}

public:
  inline constexpr Word() {}
  Word(const std::string &str);
  char operator[](int i) const;
  char& operator[](int i);
  bool operator==(const Word word) const;
  int indexOf(char ch) const;

  static constexpr Word filledWith(char letter) {
    Word word;
    for (int i = 0; i < 5; ++i) word[i] = letter;
    return word;
  }
};

std::ostream& operator<<(std::ostream& out, Word word);

#endif // WORD_H
