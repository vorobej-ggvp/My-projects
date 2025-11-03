#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;

struct eilute
{
    char slaptazodis[15];
    string slap;
    int atpaz[5];
    char lygis[10];
    string lyg;
    int min;
};

void skaityti(int &m, int &n, eilute sarasas1[], eilute sarasas2[]);
void burbulas(eilute sarasas2[], int n);
int skaicuoti(int mas1[], int mas2[]);

int main()
{
    eilute sarasas1[100], sarasas2[100];
    int m, n;
    skaityti(m, n, sarasas1, sarasas2);
    burbulas(sarasas2, n);
    for(int i = 0; i < n; i++)
    {
        cout << sarasas2[i].slap << " ";
        for(int j = 0; j < 5; j++)
        {
            cout << sarasas2[i].atpaz[j] << " ";
        }
        cout << sarasas2[i].lyg << endl;
    }
    int skirt[n];
    /*for(int j = 0; j < m; j++)
    {
        for(int i = 0; i < n; i++)
        {
            skirt[i] = skaicuoti(sarasas1[j].atpaz, sarasas2[i].atpaz);
        }
        int min = skirt[0], index = 0;
        for(int i = 0; i < n; i++)
        {
            if(min > skirt[i])
            {
                min = skirt[i];
                index = i;
            }
        }
        sarasas1[j].lyg = sarasas2[index].lyg;
        sarasas1[j].min = min;
    }
    for(int j = 0; j < m; j++)
    {
        cout << sarasas1[j].slap << " " << sarasas1[j].lyg << " " << sarasas1[j].min << endl;
    }
    /*for(int i = 0; i < m; i++)
    {
        cout << sarasas1[i].slap << " ";
        for(int j = 0 ; j < 5; j++)
        {
            cout << sarasas1[i].atpaz[j] << " ";
        }
        cout << endl;
    }*/


    return 0;
}

//-----------------------------

void skaityti(int &m, int &n, eilute sarasas1[], eilute sarasas2[])
{
    ifstream f1("in.txt");
    f1 >> m >> n;
    for(int i = 0; i < m; i++)
    {
        f1.ignore();
        f1.get(sarasas1[i].slaptazodis, 15);
        sarasas1[i].slap = sarasas1[i].slaptazodis;
        for(int j = 0 ; j < 5; j++)
        {
            f1 >> sarasas1[i].atpaz[j];
        }
    }
    for(int i = 0; i < n; i++)
    {
        f1.ignore();
        f1.get(sarasas2[i].slaptazodis, 15);
        sarasas2[i].slap = sarasas2[i].slaptazodis;
        for(int j = 0 ; j < 5; j++)
        {
            f1 >> sarasas2[i].atpaz[j];
        }
        f1.ignore();
        f1.get(sarasas2[i].lygis, 10);
        sarasas2[i].lyg = sarasas2[i].lygis;
    }
    f1.close();
}

//---------------------------------------


int skaicuoti(int mas1[], int mas2[])
{
    int ats = 0;
    for(int i = 0; i < 5; i++)
    {
        ats += abs(mas1[i] - mas2[i]);
    }
    return ats;
}

//----------------------------------------

void burbulas(eilute sarasas2[], int n)
{
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = 0; j < n - 1; j++)
        {
            if(sarasas2[j].slap.length() < sarasas2[j + 1].slap.length())
            {
                swap(sarasas2[j], sarasas2[j + 1]);
            }
        }
    }
}

//+burbulas
