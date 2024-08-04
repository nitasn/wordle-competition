#include "strategy.h"
#include "random.h"
#include <algorithm>

Word play(Game& game) {
  std::vector<Word> candidates = knownWords; 

  while (true) {
    Word guess = randomChoice(candidates);
    Word resultPattern = game.makeAGuess(guess);
    
    if (resultPattern == ALL_CORRECT) {
      return guess;
    }

    auto filteredOut = std::remove_if(
      candidates.begin(), 
      candidates.end(),
      [=](Word word) { return compareWords(guess, word) != resultPattern; }
    );
    
    candidates.erase(filteredOut, candidates.end());
  }
}
