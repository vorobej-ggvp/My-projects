#include "functions.h"

using namespace std;

bool isVowel(char c) {
    string vowels = "AEIOUaeiou";
    return vowels.find(c) != string::npos;
}

string reverseString(const string& str) {
    return string(str.rbegin(), str.rend());
}

void reverseFourthVowelWord(string& str) {
    size_t wordStart = 0;
    size_t vowelWordCount = 0;
    size_t targetWordStart = string::npos, targetWordEnd = string::npos;

    for (size_t i = 0; i < str.length();) {
        while (i < str.length() && str[i] == ' ') {
            ++i;
        }
        if (i >= str.length()) break;

        size_t currentWordStart = i;
        while (i < str.length() && str[i] != ' ') {
            ++i;
        }
        size_t currentWordEnd = i;

        if (isVowel(str[currentWordStart])) {
            ++vowelWordCount;
        }
    }

    size_t targetVowelWordIndex = vowelWordCount - 4;
    vowelWordCount = 0;

    for (size_t i = 0; i < str.length();) {
        while (i < str.length() && str[i] == ' ') {
            ++i;
        }
        if (i >= str.length()) break;

        size_t currentWordStart = i;
        while (i < str.length() && str[i] != ' ') {
            ++i;
        }
        size_t currentWordEnd = i;

        if (isVowel(str[currentWordStart])) {
            if (vowelWordCount == targetVowelWordIndex) {
                targetWordStart = currentWordStart;
                targetWordEnd = currentWordEnd;
                break;
            }
            ++vowelWordCount;
        }
    }

    if (targetWordStart != string::npos && targetWordEnd != string::npos) {
        string reversedWord = reverseString(str.substr(targetWordStart, targetWordEnd - targetWordStart));
        str.replace(targetWordStart, targetWordEnd - targetWordStart, reversedWord);
    }
}
