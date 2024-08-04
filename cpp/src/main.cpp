#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include <chrono>
#include <cassert>

#include "random.h"
#include "engine.h"
#include "strategy.h"

void measure_strategy(int N) {
  std::vector<int> list_num_guesses;
  auto start = std::chrono::high_resolution_clock::now();

  for (int i = 0; i < N; ++i) {
    Word secretWord = randomChoice(knownWords);
    Game game(secretWord);
    assert(play(game) == secretWord);
    list_num_guesses.push_back(game.numGuessesMade());
  }

  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end - start;

  double sum = std::accumulate(list_num_guesses.begin(), list_num_guesses.end(), 0.0);
  double mean = sum / N;
  double sq_sum = std::inner_product(list_num_guesses.begin(), list_num_guesses.end(), list_num_guesses.begin(), 0.0);
  double stdev = std::sqrt(sq_sum / N - mean * mean);

  std::cout
    << '\n'
    << "Played " << N << " Games" << '\n'
    << "Average  Num Guesses = " << mean << '\n'
    << "Std.Dev. Num Guesses = " << stdev << '\n'
    << '\n'
    << "Completed in " << elapsed.count() << " seconds" << '\n';
}

int main() {
  measure_strategy(1);
}
