#include "word.h"
#include "engine.h"

#include <cassert>
#include <sstream>

Word::Word(const std::string &str) : bits(0) {
  assert(str.size() == 5);
  for (size_t i = 0; i < 5; ++i) {
    char ch = 'A' <= str[i] && str[i] <= 'Z' ? std::tolower(str[i]) : str[i];
    this->bits |= static_cast<uint64_t>(ch) << (i * 8);
  }
}

char Word::operator[](int i) const {
  uint64_t mask = UINT64_C(0xFF) << (i * 8);
  uint64_t result = (this->bits & mask) >> (i * 8);
  return static_cast<char>(result);
}

char& Word::operator[](int i) {
  #if defined(__BYTE_ORDER__) && (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
    return reinterpret_cast<char*>(&this->bits)[i];
  #elif defined(__BYTE_ORDER__) && (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
    return reinterpret_cast<char*>(&this->bits)[7 - i];
  #else
    #error "Endianness not detected"
  #endif
}

bool Word::operator==(const Word word) const {
  return this->bits == word.bits;
}

int Word::indexOf(char ch) const {
  for (int i = 0; i < 5; ++i) {
    if (this->operator[](i) == ch) {
      return i;
    }
  }
  return -1;
}

static const char* toUnicode(char ch) {
  switch (ch) {
    case LETTER_NOT_IN_WORD: return "⬜";
    case CORRECT_LETTER_WRONG_INDEX: return "🟨";
    case CORRECT_LETTER_CORRECT_INDEX: return "🟩";
    default: return "?";
  }
}

std::ostream& operator<<(std::ostream& out, Word word) {
  for (int i = 0; i < 5; ++i) {
    char ch = word[i];
    if ('a' <= ch && ch <= 'z') {
      out << static_cast<char>(std::toupper(ch));
    } else {
      out << toUnicode(ch);
    }
  }
  return out;
}
