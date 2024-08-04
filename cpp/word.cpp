#include "word.h"

Word::Word(const std::string &str) : bits(0) {
  assert(str.size() == 5);
  for (size_t i = 0; i < 5; ++i) {
    this->bits |= static_cast<uint64_t>(str[i]) << (i * 8);
  }
}

Word::Word(const char* str) : bits(0) {
  assert(strlen(str) == 5);
  for (size_t i = 0; i < 5; ++i) {
    this->bits |= static_cast<uint64_t>(str[i]) << (i * 8);
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