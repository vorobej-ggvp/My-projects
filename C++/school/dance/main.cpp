#include <iostream>
#include <fstream>

using namespace std;

struct eilute
{
    char vardai[20];
    string vardas;
    int technika[100];
    int artiskuma[100];
    int rez;
};

void skaityti(eilute sarasas[], int &p, int &t);

void burbulas(int x[], int &t);
void suma(eilute sarasas[], int &p, int &t);

void burbulas_rez(eilute sarasas[], int &p);

int main()
{
    eilute sarasas[100];
    int p, t;

    skaityti(sarasas, p, t);

    for(int i = 0; i < p; i++)
    {
        burbulas(sarasas[i].technika, t);
        burbulas(sarasas[i].artiskuma, t);
    }
    suma(sarasas, p, t);
    burbulas_rez(sarasas, p);
    for(int i = 0; i < p; i++)
        cout << sarasas[i].vardas << " " << sarasas[i].rez << endl;
    return 0;
}

//=============================================

void skaityti(eilute sarasas[], int &p, int &t)
{
    ifstream f1 ("in.txt");
    f1 >> p >> t;
    for(int i = 0; i < p; i++)
    {
        f1.ignore();
        f1.get(sarasas[i].vardai, 20);
        sarasas[i].vardas = sarasas[i].vardai;
        for(int j = 0; j < t; j++)
        {
            f1 >> sarasas[i].technika[j];
        }
        for(int j = 0; j < t; j++)
        {
            f1 >> sarasas[i].artiskuma[j];
        }
    }
    f1.close();
}

//================================================

void burbulas(int x[], int &t)
{
    for(int i = 0; i < t - 1; i++)
        for(int j = 0; j < t - 1; j++)
            if(x[j] > x[j + 1])
                swap(x[j], x[j + 1]);
}

void suma(eilute sarasas[], int &p, int &t)
{
    for(int i = 0; i < p; i++)
    {
        for(int j = 1; j < t - 1; j++)
        {
            sarasas[i].rez += sarasas[i].technika[j];
        }
        for(int j = 1; j < t - 1; j++)
        {
           sarasas[i].rez += sarasas[i].artiskuma[j];
        }
    }
}

//==============================================

void burbulas_rez(eilute sarasas[], int &p)
{
    for(int k = 0; k < p; k++)
    {
        for(int i = 0;  i < p - 1; i++)
        {
            if(sarasas[i].rez < sarasas[i + 1].rez)
                swap(sarasas[i], sarasas[i + 1]);
        }
    }
}
