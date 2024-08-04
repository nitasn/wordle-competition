#include "random.h"

Random::Random(size_t max) : gen(rd()), distr(0, max - 1) {}

size_t Random::next() {
  return distr(gen);
}

size_t randrange(size_t N) {
  return Random(N).next();
}