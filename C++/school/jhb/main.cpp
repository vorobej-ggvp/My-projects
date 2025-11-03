#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

struct eilute
{
    string prek;
    int kiek;
    double kaina;
    int kiekis = 0;
    double sum = 0.0;
};

void skaityti(eilute viskas, vector<eilute> &mas, string &line);
void skaicuoti(vector<eilute> mas, vector<eilute> &mas1);
void burbulas(vector<eilute> &mas1);
void rasyti(vector<eilute> mas1);

int main()
{
    eilute viskas;
    vector<eilute> mas, mas1;
    string line;
    skaityti(viskas, mas, line);
    skaicuoti(mas, mas1);
    burbulas(mas1);
    rasyti(mas1);
    return 0;
}

//=================================

void skaityti(eilute viskas, vector<eilute> &mas, string &line)
{
    ifstream f1("U2.txt");
    while(getline(f1, line))
    {
        stringstream ss(line);
        ss >> viskas.prek >> viskas.kiek >> viskas.kaina;
        mas.push_back(viskas);
    }
    f1.close();
}

//===========================================

void skaicuoti(vector<eilute> mas, vector<eilute> &mas1)
{
    for(const auto& n : mas)
    {
        bool yra = 0;
        for(auto& s : mas1)
        {
            if(n.prek == s.prek)
            {
                s.kiekis += n.kiek;
                s.sum += n.kiek * n.kaina;
                yra = true;
                break;
            }
        }
        if(!yra)
        {
            eilute naujas;
            naujas.prek = n.prek;
            naujas.kiekis = n.kiek;
            naujas.sum = n.kaina * n.kiek;
            mas1.push_back(naujas);
        }
    }
}

//====================================

void burbulas(vector<eilute> &mas1)
{
    for(int i = 0; i < mas1.size() - 1; i++)
        for(int j = 0; j < mas1.size() - 1; j++)
            if(mas1[j].sum < mas1[j + 1].sum)
                swap(mas1[j], mas1[j + 1]);
}

//====================================

void rasyti(vector<eilute> mas1)
{
    ofstream f2("U2rez.txt");
    f2 << "Pardavimų suvestinė:" << endl;
    for(const auto& i : mas1)
    {
        f2 << i.prek << "kiekis: " << i.kiekis << ", suma: " << fixed << setprecision(2) << i.sum << " €" << endl;
    }
    f2.close();
}
