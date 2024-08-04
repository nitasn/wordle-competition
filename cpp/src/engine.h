#ifndef ENGINE_H
#define ENGINE_H

#include "word.h"
#include "known_words.h"

enum PatternResult : char {
  LETTER_NOT_IN_WORD = 0x0,          // ⬜
  CORRECT_LETTER_WRONG_INDEX = 0x1,  // 🟨
  CORRECT_LETTER_CORRECT_INDEX = 0x2 // 🟩
};

const Word ALL_CORRECT = Word::filledWith(CORRECT_LETTER_CORRECT_INDEX);

Word compareWords(Word guess, Word secret);

class Game {
private:
  Word secretWord;
  int guessesMade;

public:
  Game();
  Game(Word secretWord);
  Word makeAGuess(Word guess);
  int numGuessesMade() const;
};

#endif // ENGINE_H
