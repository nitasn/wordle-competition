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

If setting the secret to FIGHT and fixing the first guess to LIGHT, the game goes like:
```
Guessed LIGHT and got ⬜🟩🟩🟩🟩
Guessed ABERS and got ⬜⬜⬜⬜⬜
Guessed KNOWD and got ⬜⬜⬜⬜⬜
Guessed FIGHT and got 🟩🟩🟩🟩🟩
```

If setting the secret to EIGHT and fixing the first guess to EIGHT, the game goes like:
```
Guessed LIGHT and got ⬜🟩🟩🟩🟩
Guessed ABERS and got ⬜⬜🟨⬜⬜
Guessed EIGHT and got 🟩🟩🟩🟩🟩
```