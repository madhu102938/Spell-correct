# Spell-correct
This is simple implementation of Damerau–Levenshtein distance algorithm in c++

Enter a word, if it is incorrect, then it will suggest a possible correct word

## Steps to run this
- Make sure `main_file.cpp` and `words_alpha.txt` are the same directory
- Run `main_file.cpp`
- It takes in two arguments
     1. path to word list (one word per line)
     2. The word which you want to check
  - Returns a vector of words that are closest to the word
- Use the `check` method to get word suggestions
- Enter a word (doesn't work for sentences)
