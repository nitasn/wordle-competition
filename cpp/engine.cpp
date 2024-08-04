#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>
#include <random>
#include <cstdint>

std::vector<char[5]> loadWords(const std::string& filename) {
  std::ifstream file(filename);

  if (!file.is_open()) {
    std::cerr << "Failed to open file: " << filename << std::endl;
    exit(EXIT_FAILURE);
  }

  size_t totalLetters = 0, currentWordLength;
  char ch;

  while (file.get(ch)) {
    if ('a' <= ch && ch <= 'z') {
      ++totalLetters;
      ++currentWordLength;
    } else {
      if (currentWordLength % 5) {
        std::cerr << "All known words must have 5 letters (found '" << currentWordLength << "')" << std::endl;
        exit(EXIT_FAILURE);
      }
      currentWordLength = 0;
    }
  }

  file.seekg(0);

  file.close();
  return totalLetters;
}

enum PatternItem : char {
  LETTER_NOT_IN_WORD = 0x1,
  CORRECT_LETTER_WRONG_INDEX = 0x2,
  CORRECT_LETTER_CORRECT_INDEX = 0x3,
};


std::string compareWords(const std::string& guess, const std::string& secret) {
  assert(guess.size() == 5 && secret.size() == 5);

  std::string result = std::string(5, LETTER_NOT_IN_WORD[0]);
  std::string mutableGuess = guess;
  std::string mutableSecret = secret;

  for (int idx = 0; idx < 5; ++idx) {
    if (mutableGuess[idx] == mutableSecret[idx]) {
      mutableGuess[idx] = '_';
      mutableSecret[idx] = '_';
      result[idx] = CORRECT_LETTER_CORRECT_INDEX[0];
    }
  }

  for (int idx = 0; idx < 5; ++idx) {
    if (mutableGuess[idx] != '_' && mutableSecret.find(mutableGuess[idx]) != std::string::npos) {
      mutableSecret[mutableSecret.find(mutableGuess[idx])] = '_';
      result[idx] = CORRECT_LETTER_WRONG_INDEX[0];
    }
  }
  
  return result;
}

class Game {
private:
  std::string secretWord;
  int guessesMade;

public:
  Game(const std::vector<std::string>& knownWords) : guessesMade(0) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, knownWords.size() - 1);
    secretWord = knownWords[distr(gen)];
  }

  std::string makeAGuess(const std::string& guess) {
    ++guessesMade;
    return compareWords(guess, secretWord);
  }

  int numGuessesMade() const {
    return guessesMade;
  }
};

void test() {
  std::cout << "testing the engine...\n";
  std::vector<std::string> words = {"hello", "kelly", "kohen"};
  Game game(words);
  game.secretWord = "hello";  // This line should be modified if you want to keep the encapsulation

  assert(game.makeAGuess("fatut") == "⬜⬜⬜⬜⬜");
  assert(game.makeAGuess("ehoaa") == "🟨🟨🟨⬜⬜");
  assert(game.makeAGuess("helll") == "🟩🟩🟩🟩⬜");
  assert(game.makeAGuess("hello") == "🟩🟩🟩🟩🟩");
  
  assert(game.numGuessesMade() == 4);
  std::cout << "engine tests passed :)\n";
}

int main() {
  test();
  return 0;
}
