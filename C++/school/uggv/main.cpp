#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct eilute
{
    string vardas;
    double kiek;
    double vid;
};

void skaityti(string line, eilute viskas, vector<eilute> &str);
double visk_vid(vector<eilute> &str);
int daug_vid_b(vector<eilute> &str, double ben_vid);
int daug_vid_m(vector<eilute> &str, double ben_vid);

int main()
{
    string line;
    eilute viskas;
    vector<eilute> str;
    skaityti(line, viskas, str);
    double ben_vid = visk_vid(str);
    int kas[2]{daug_vid_b(str, ben_vid), daug_vid_m(str, ben_vid)};
    for(int i = 0; i < str.size(); i++)
    {
        cout << str[i].vardas << " " << str[i].kiek << " " << str[i].vid << endl;
    }
    cout << ben_vid << endl << endl;
    for(int i = 0; i < sizeof(kas) / sizeof(kas[0]); i++)
        cout << kas[i] << endl;
    return 0;
}

//=====================================

void skaityti(string line, eilute viskas, vector<eilute> &str)
{
    ifstream f1("in.csv");
    while(getline(f1, line))
    {
        stringstream ss(line);
        getline(ss, viskas.vardas, ';');
        ss >> viskas.kiek;
        ss.ignore(1, ';');
        ss >> viskas.vid;
        str.push_back(viskas);
    }
    f1.close();

}

//=====================================

double visk_vid(vector<eilute> &str)
{
    int x = 0;
    double sum = 0;
    for(int i = 0; i < str.size(); i++)
    {
        sum += str[i].vid;
        x++;
    }
    return sum / x;
}

//=====================================

int daug_vid_b(vector<eilute> &str, double ben_vid)
{
    int x = 0;
    for(int i = 0; i < str.size(); i++)
    {
        if(str[i].vid > ben_vid && str[i].vardas == "bern")
        {
            x++;
        }
    }
    return x;
}

//==========================================

int daug_vid_m(vector<eilute> &str, double ben_vid)
{
    int x = 0;
    for(int i = 0; i < str.size(); i++)
    {
        if(str[i].vid > ben_vid && str[i].vardas == "merg")
        {
            x++;
        }
    }
    return x;
}
