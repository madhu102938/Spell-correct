# Spell-correct
This is simple implementation of Damerau–Levenshtein distance algorithm in c++

Enter a word, if it is incorrect, then it will suggest a possible correct word

## Steps to run this
- Make sure `main_file.cpp` and `words_alpha.txt` are the same directory
- Run `main_file.cpp`
- Initiate the object of `SpellChecker` with your choice of word list
  - Replace the `words_alpha.txt` with your choice of words
  - make sure that its one word per line
- Use the `check` method to get word suggestions
- Enter a word (doesn't work for sentences)
