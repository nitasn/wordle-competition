## C++ Wordle Solver

A (much) faster version, written in C++.

Using a `Word` class that wraps a `uint64_t`, and exposes an `operator[]`. No pointers / indirections involved.

## Todo

1. Precompute `compareWords(Word guess, Word secret)` and use a look-up table.

2. These cases occur:

```
Guessed TARES and got 🟨⬜⬜🟨🟨
Guessed SPITE and got 🟩⬜🟩🟩🟩
Guessed SHITE and got 🟩⬜🟩🟩🟩
Guessed SKITE and got 🟩⬜🟩🟩🟩
Guessed SMITE and got 🟩⬜🟩🟩🟩
Guessed SUITE and got 🟩🟩🟩🟩🟩
```

After getting 🟩⬜🟩🟩🟩 for SPITE, 
wasn't there a better word to guess? something with the letters HKMU?