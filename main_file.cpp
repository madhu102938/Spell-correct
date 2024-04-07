#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
#define endl '\n'

bool search(vector<string> &words, string &input)
{
    int low = 0, high = words.size() - 1;

    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (words[mid] == input)
            return true;
        else if (words[mid] < input)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return false;
}

// int distance(int i, int j, string &word, string &input)
// {
//     if (i < 0)
//         return 1 + j;
//     if (j < 0)
//         return 1 + i;

//     if (word[i] == input[j])
//         return distance(i - 1, j - 1, word, input);
//     else
//     {
//         int del, ins, rep, trans;
//         del = ins = rep = trans = INT_MAX;

//         del = 1 + distance(i, j - 1, word, input);
//         ins = 1 + distance(i - 1, j, word, input);
//         rep = 1 + distance(i - 1, j - 1, word, input);
/*
         if (i > 0 && j > 0)
         {
            if ((word[i-1] == input[j]) && (word[i] == input[j-1]))
                trans = 1 + distance(i-2, j-2, word, input);
         }
*/
//         return min(del, min(ins, rep));
//     }
// }

int distance(string &word, string &input)
{
    int n = word.size();
    int m = input.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 0; i <= n; i++)
        dp[i][0] = i;

    for (int j = 0; j <= m; j++)
        dp[0][j] = j;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (word[i - 1] == input[j - 1])
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
                    if ((word[i - 2] == input[j - 1]) && (word[i - 1] == input[j - 2]))
                        trans = 1 + dp[i - 2][j - 2]; // distance(i - 2, j - 2, word, input);
                }

                dp[i][j] = min(min(del, trans), min(ins, rep));
            }
        }
    }

    return dp[n][m];
}

int main()
{

    ifstream my_file("words_alpha.txt");
    string line;
    vector<string> words;

    while (!my_file.eof())
    {
        getline(my_file, line);
        words.push_back(line);
    }
    my_file.close();

    string input;
    cin >> input;
    transform(input.begin(), input.end(), input.begin(), ::tolower);
    vector<string> possibleWords;
    int minDistance = INT_MAX;
    int n = input.size();
    int temp;

    if (!search(words, input))
    {
        for (string word : words)
        {
            int m = word.size();
            if (abs(n - m) <= minDistance)
            {
                temp = distance(word, input);
                if (temp == minDistance)
                {
                    possibleWords.push_back(word);
                }
                else if (temp < minDistance)
                {
                    minDistance = temp;
                    possibleWords.clear();
                    possibleWords.push_back(word);
                }
            }
        }
    }

    cout << endl << "=====================" << endl;

    if (minDistance == INT_MAX)
        cout << "No mistake" << endl;
    else
    {
        cout << "min distance is : " << minDistance << endl;
        cout << "=====================" << endl << "Possible words are : " << "\n\n";

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