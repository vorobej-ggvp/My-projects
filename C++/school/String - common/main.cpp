#include <iostream>
#include <string>
#include "functions.h"

using namespace std;

int main() {
    string input;
    cout << "¬ведите строку: ";
    getline(cin, input);

    reverseFourthVowelWord(input);

    cout << "–езультат: " << input << endl;
    return 0;
}
