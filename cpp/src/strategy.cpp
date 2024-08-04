#include "strategy.h"
#include "random.h"

#include <iostream>
#include <algorithm>
#include <cmath>

// since each char in the pattern is either { 0x0, 0x1, 0x2 }, and the pattern's length is 5,
// we can map the pattern into a number between 0 and 3^5 (= 243).
int mapPatternToNumberUpTo243(Word pattern) {
  int result = 0;
  int powerOfThree = 1;
  for (int i = 0; i < 5; ++i) {
    result += powerOfThree * pattern[i];
    powerOfThree *= 3;
  }
  return result;
}

void resultsPatternHistogram(Word guess, const std::vector<Word>& candidates, int histogram[243]) {
  std::fill(histogram, histogram + 243, 0);
  for (Word maybeSecretWord : candidates) {
    Word result = compareWords(guess, maybeSecretWord);
    histogram[mapPatternToNumberUpTo243(result)] += 1;
  }
}

double entropy(int histogram[243], size_t numCandidates) {
  double entropy = 0.0;
  for (int i = 0; i < 243; ++i) {
    if (histogram[i]) {
      double p = static_cast<double>(histogram[i]) / numCandidates;
      entropy -= p * std::log2(p);
    }
  }
  return entropy;
}

Word bestCandidate(const std::vector<Word>& candidates) {
  if (candidates.size() == knownWords.size()) {
    return Word(std::string("tares"));
  }

  if (candidates.size() == 1) {
    return candidates[0];
  }

  int histogram[243];

  Word bestGuess;
  double bestScore = 0;

  for (Word guess : candidates.size() > 5 ? knownWords: candidates) {
    resultsPatternHistogram(guess, candidates, histogram);
    double score = entropy(histogram, candidates.size());

    if (score > bestScore) {
      bestGuess = guess;
      bestScore = score;
    }
  }

  return bestGuess;
}

const char* toUnicode(char ch) {
  switch (ch) {
    case LETTER_NOT_IN_WORD: return "⬜";
    case CORRECT_LETTER_WRONG_INDEX: return "🟨";
    case CORRECT_LETTER_CORRECT_INDEX: return "🟩";
    default: return "?";
  }
}

std::string toUpperCase(const std::string& input) {
  std::string result = input;
  std::transform(result.begin(), result.end(), result.begin(),
                 [](auto c) { return std::toupper(c); });
  return result;
}

Word play(Game& game) {
  std::vector<Word> candidates = knownWords; 
  std::cout << '\n';

  while (true) {
    Word guess = bestCandidate(candidates);
    Word resultPattern = game.makeAGuess(guess);

    std::cout << "guessed " << toUpperCase(guess.toString()) << " and got ";
    for (int i = 0; i < 5; ++i) {
      std::cout << toUnicode(resultPattern[i]);
    }
    std::cout << '\n';

    if (resultPattern == ALL_CORRECT) {
      return guess;
    }

    auto filteredOut = std::remove_if(
      candidates.begin(), 
      candidates.end(),
      [=](Word word) { return compareWords(guess, word) != resultPattern; }
    );

    candidates.erase(filteredOut, candidates.end());

    if (game.numGuessesMade() > 15) exit(0);
  }
}
