#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
int countEmptySpace(const std::string& word, int n = 0);
void findWord(const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict,
    int emptySpace,
    string tempWord,
    set<string>& wordSet);
void findCombination(const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict,
    int emptySpace,
    string tempWord,
    set<string>& wordSet,
    int n = 0);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    int empty_space = countEmptySpace(in);
    string temp_word = "";
    set<string> SuitableWordSet;
    findWord(in, floating, dict, empty_space, temp_word, SuitableWordSet);
    cout << "before" << endl;
    for (string words : SuitableWordSet)
    {
        cout << words << endl;
    }
    return SuitableWordSet;
}

// Define any helper functions here
// function counts how many empty spaces the word has
int countEmptySpace(const std::string& word, int n)
{
    if (n >= word.size())
    {
        return 0;
    }
    if (word[n] == '-')
    {
        return 1 + countEmptySpace(word, n+1);
    }
    else
    {
        return countEmptySpace(word, n+1);
    }
}

// find the words that fit the category
void findWord(const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict,
    int emptySpace,
    string tempWord,
    set<string>& wordSet)
    {
        // base case: if the word is in dictionary just return
        if (tempWord.length() == in.length())
        {
          if (dict.find(tempWord) != dict.end())
          {
              wordSet.insert(tempWord);
              return;
          }
        }

        // if the input word has a fixed letter here, then we add to the tempWord directly
        if (in[tempWord.size()] != '-')
        {
            // now recurse the next position
            findWord(in, floating, dict, emptySpace, tempWord + in[tempWord.size()], wordSet);
        }
        // if the input word has '-', then use another resursive function
        else
        {
            findCombination(in, floating, dict, emptySpace, tempWord, wordSet);
        }
    }

void findCombination(const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict,
    int emptySpace,
    string tempWord,
    set<string>& wordSet,
    int n) // n here is the character position
    {
        // 1. if the number of empty space is equal to the floating, we only need to check the floating paritions
        if (emptySpace <= floating.size())
        {
            if (n == floating.size())
            {
                return;
            }
            string temp_floating = floating;
            temp_floating.erase(temp_floating.find(floating[n]), 1);
            findWord(in, temp_floating, dict, emptySpace - 1, tempWord + floating[n], wordSet);
            findCombination(in, floating, dict, emptySpace, tempWord, wordSet, n + 1);
        }
        // 2. if there are more empty spaces, then we need to check from a to z
        else
        {
            for (char letter = 'a'; letter <= 'z'; letter++)
            {
                // if the letter is not in floating
                if (floating.find(letter) == string::npos)
                {
                    findWord(in, floating, dict, emptySpace - 1, tempWord + letter, wordSet);
                }
                // if the letter is in floating
                else
                {
                    string temp_floating = floating;
                    temp_floating.erase(temp_floating.find(letter), 1);
                    findWord(in, temp_floating, dict, emptySpace - 1, tempWord + letter, wordSet);
                }
            }
        }
    }