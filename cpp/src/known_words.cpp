#include "known_words.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

std::string readFile(const std::string& filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Failed to open file: " << filename << std::endl;
    exit(EXIT_FAILURE);
  }

  std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
  file.close();
  return content;
}

std::vector<Word> readWordsFromFile(const std::string& filename) {
  std::string content = readFile(filename);
  std::istringstream iss(content);
  std::vector<Word> words;
  
  std::string word;
  while (iss >> word) {
    words.emplace_back(word);
  }

  return words;
}

std::vector<Word> knownWords = readWordsFromFile("../known_words.txt");
