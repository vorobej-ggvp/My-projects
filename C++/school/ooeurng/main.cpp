#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct eilute
{
    string sal1;
    string sal2;
    int kiek;
};

void skaityti(string &line, vector<eilute> &str, eilute viskas);

int main()
{
    string line;
    vector<eilute> str;
    eilute viskas;
    skaityti(line, str, viskas);
    for(int i = 0; i < str.size(); i++)
    {
        cout << str[i].sal1 << " " << str[i].sal2 << " " << str[i].kiek << endl;
    }
}

//========================================

void skaityti(string &line, vector<eilute> &str, eilute viskas)
{
    ifstream f1("Eurovizija.csv");
    while(getline(f1, line))
    {
        stringstream ss(line);
        getline(ss, viskas.sal1, ';');
        getline(ss, viskas.sal2, ';');
        ss >> viskas.kiek;
        str.push_back(viskas);
    }
    f1.close();
}
