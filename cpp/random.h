#ifndef RANDOM_H
#define RANDOM_H

#include <random>

class Random {
private:
  std::random_device rd;
  std::mt19937 gen;
  std::uniform_int_distribution<> distr;

public:
  Random(size_t max);
  size_t next();
};

size_t randrange(size_t N);

inline auto randomChoice(const auto& container) {
  return container[randrange(container.size())];
}

#endif // RANDOM_H
