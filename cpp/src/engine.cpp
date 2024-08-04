#include "engine.h"
#include "random.h"

Word compareWords(Word guess, Word secret) {
  Word result = Word::filledWith(LETTER_NOT_IN_WORD);

  for (int idx = 0; idx < 5; ++idx) {
    if (guess[idx] == secret[idx]) {
      guess[idx] = '_';
      secret[idx] = '_';
      result[idx] = CORRECT_LETTER_CORRECT_INDEX;
    }
  }

  for (int idx = 0; idx < 5; ++idx) {
    if (guess[idx] == '_') continue;
    int secret_idx = secret.indexOf(guess[idx]);
    if (secret_idx != -1) {
      secret[secret_idx] = '_';
      result[idx] = CORRECT_LETTER_WRONG_INDEX;
    }
  }

  return result;
}

Game::Game() : secretWord(randomChoice(knownWords)), guessesMade(0) {}

Game::Game(Word secretWord) : secretWord(secretWord), guessesMade(0) {}

Word Game::makeAGuess(Word guess) {
  guessesMade++;
  return compareWords(guess, secretWord);
}

int Game::numGuessesMade() const {
  return guessesMade;
}
