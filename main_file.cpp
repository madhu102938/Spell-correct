#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
// #include "SpellChecker.h"
using namespace std;
#define endl '\n'

// class SpellChecker {
// private:
//     vector<string> dictionary;

//     bool search(const string &word);
//     int distance(const string &word1, const string &word2);

// public:
//     SpellChecker(const vector<string> &words);
//     void toLowerCase(string &input);
//     pair<int, vector<string>> check(string input);
// };

class SpellChecker
{
private:
    vector<string> dictionary;

    bool search(const string &word)
    {
        // Implement search functionality
        // Return true if word is in dictionary

        int low = 0, high = dictionary.size() - 1;

        while (low <= high)
        {
            int mid = (low + high) / 2;
            if (dictionary[mid] == word)
                return true;
            else if (dictionary[mid] < word)
                low = mid + 1;
            else
                high = mid - 1;
        }
        return false;
    }

    int distance(const string &word1, const string &word2)
    {
        // Implement distance calculation
        // Return the distance between word1 and word2
        int n = word1.size();
        int m = word2.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        for (int i = 0; i <= n; i++)
            dp[i][0] = i;

        for (int j = 0; j <= m; j++)
            dp[0][j] = j;

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (word1[i - 1] == word2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1]; // distance(i - 1, j - 1, word, input);
                else
                {
                    int del, ins, rep, trans;
                    del = ins = rep = trans = INT_MAX;

                    del = 1 + dp[i][j - 1];     // distance(i, j - 1, word, input);
                    ins = 1 + dp[i - 1][j];     // distance(i - 1, j, word, input);
                    rep = 1 + dp[i - 1][j - 1]; // distance(i - 1, j - 1, word, input);

                    if (i > 1 && j > 1)
                    {
                        if ((word1[i - 2] == word2[j - 1]) && (word1[i - 1] == word2[j - 2]))
                            trans = 1 + dp[i - 2][j - 2]; // distance(i - 2, j - 2, word, input);
                    }

                    dp[i][j] = min(min(del, trans), min(ins, rep));
                }
            }
        }

        return dp[n][m];
    }

public:
    SpellChecker(const vector<string> &words) : dictionary(words) {}

    void toLowerCase(string &input)
    {
        // Implement toLowerCase functionality
        transform(input.begin(), input.end(), input.begin(), ::tolower);
    }

    pair<int, vector<string>> check(string input)
    {
        /*
            Implement the spell checker function
            Takes in a string input
            Return a pair of integer and vector of strings
            The integer is the minimum distance between the input and the words in the dictionary
            The vector of strings contains all the words in the dictionary that have the minimum distance
        */
        toLowerCase(input);
        vector<string> possibleWords;
        int minDistance = INT_MAX;

        if (!search(input))
        {
            for (const string &word : dictionary)
            {
                int temp = distance(word, input);
                if (temp < minDistance)
                {
                    possibleWords.clear();
                    minDistance = temp;
                    possibleWords.push_back(word);
                }
                else if (temp == minDistance)
                {
                    possibleWords.push_back(word);
                }
            }
        }

        return {minDistance, possibleWords};
    }
};

int main(int argc, char *argv[]) {

    string dictionaryFile, input;
    if (argc == 3)
    {
        dictionaryFile = argv[1];
        input = argv[2];
    }
    else
    {
        cin >> dictionaryFile;
    }

    ifstream my_file(dictionaryFile);
    if (!my_file) {
        cerr << "Error opening file: " << dictionaryFile << endl;
        return 1;
    }

    string line;
    vector<string> words;

    while (!my_file.eof())
    {
        getline(my_file, line);
        words.push_back(line);
    }
    my_file.close();

    cin >> input;

    SpellChecker obj(words);

    pair<int, vector<string>> result = obj.check(input);
    int minDistance = result.first;
    vector<string> possibleWords = result.second;

    cout << endl
         << "=====================" << endl;

    if (minDistance == INT_MAX)
        cout << "No mistake" << endl;
    else
    {
        cout << "min distance is : " << minDistance << endl;
        cout << "=====================" << endl
             << "Possible words are : " << "\n\n";

        for (string word : possibleWords)
            cout << word << endl;
        cout << endl;
    }

    /*
        1. size difference bigger than minimum distance you have?
        3. Start with INT_MAX min_distance at start
        4. If your distance might be higher than min_distance don't compare
        2. that's it for now : )
        5. max size is 31, total number words are 370106
    */

    return 0;
}