## `strategy.py`
Your goal is to write a `play` function. It takes a `Game` instance and returns the secret word.

```py
from engine import Game, KNOWN_WORDS, compare_words
import random

def play(game: Game) -> str:
  """
  Plays the game and finds the secret word.
  """
  # Your code here...

  # Example strategy:

  candidates = KNOWN_WORDS
  
  while True:
    guess = random.choice(candidates)
    result_pattern = game.make_a_guess(guess)
    
    if result_pattern == "🟩🟩🟩🟩🟩":
      return guess
    
    candidates = [word for word in candidates if compare_words(guess, word) == result_pattern]
```

## `engine.py`

Provides the game essentials:

```py
LETTER_NOT_IN_WORD = "⬜"
CORRECT_LETTER__WRONG_INDEX = "🟨"
CORRECT_LETTER__CORRECT_INDEX = "🟩"


def compare_words(guess: str, secret: str) -> str:
  """
  >>> compare_words("hello", "kelly") == "⬜🟩🟩🟩⬜"
  >>> compare_words("hello", "kohen") == "🟨🟨⬜⬜🟨"
  """
  ...


KNOWN_WORDS = ["ahead", "hello", ...]  # 14855 words


class Game:
  def __init__(self):
    self.__secret_word = random.choice(KNOWN_WORDS)
    self.__guesses_made = 0
  
  def make_a_guess(self, guess: str):
    """
    returns a pattern such as "🟩🟨🟨⬜⬜"
    """
    self.__guesses_made += 1
    return compare_words(guess, self.__secret_word)
  
  def num_guesses_made(self):
    return self.__guesses_made
```

## `main.py`
Measures how efficient (in number of guesses) the strategy is.

```
$ py main.py

    Played 100 Games
    Average Num Guesses = 5.420
    Std.Dev Num Guesses = 1.634
```