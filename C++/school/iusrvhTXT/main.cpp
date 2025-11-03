#include <iostream>
#include <fstream>

using namespace std;

struct eilute
{
    string mar;
    string mod;
    int metai;
    int kaina;
    int rida;
};

void skaityti(string &a1, string & a2, string &a3, string &a4, string &a5, int &n, eilute sarasas[]);
void ieskoti(eilute sarasas[], int n, eilute nauj_sarasas[], int &index);
void burbulas(eilute nauj_sarasas[], int n);

int main()
{
    eilute sarasas[100], nauj_sarasas[100];
    string a1, a2, a3, a4, a5;
    int n, index;
    skaityti(a1, a2, a3, a4, a5, n, sarasas);
    ieskoti(sarasas, n, nauj_sarasas, index);
    burbulas(nauj_sarasas, index);
    cout << a1 << " " <<  a2 << " " <<  a3 << " " <<  a4 << " " <<  a5 << endl;
    for(int i = 0; i < index; i++)
    {
        cout << nauj_sarasas[i].mar << " " << nauj_sarasas[i].mod << " " << nauj_sarasas[i].metai << " " << nauj_sarasas[i].kaina << " " << nauj_sarasas[i].rida << endl;
    }
    return 0;
}

//------------------------------------------------------

void skaityti(string &a1, string & a2, string &a3, string &a4, string &a5, int &n, eilute sarasas[])
{
    ifstream f1("in.txt");
    f1 >> n >> a1 >> a2 >> a3 >> a4 >> a5;
    for(int i = 0; i < n; i++)
    {
        f1 >> sarasas[i].mar >> sarasas[i].mod >> sarasas[i].metai >> sarasas[i].kaina >> sarasas[i].rida;
    }
    f1.close();
}

//--------------------------------------------------------

void ieskoti(eilute sarasas[], int n, eilute nauj_sarasas[], int &index)
{
    index = 0;
    for(int i = 0; i < n; i++)
    {
        if(sarasas[i].metai >= 2018 && sarasas[i].rida < 50000 && sarasas[i].kaina <= 20000)
        {
            nauj_sarasas[index] = sarasas[i];
            index++;
        }
    }
}

//----------------------------------------------------

void burbulas(eilute nauj_sarasas[], int n)
{
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = 0; j < n - 1; j++)
        {
            if(nauj_sarasas[j].kaina > nauj_sarasas[j + 1].kaina)
                swap(nauj_sarasas[j], nauj_sarasas[j + 1]);
        }
    }
}
