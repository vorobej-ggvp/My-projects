#include <iostream>
#include <fstream>
#define forLoop(vari, len) for(int vari = 0; vari < len; vari++)
#define maz 10
#define did 30

using namespace std;

struct eilute
{
    char vardas[20];
    string vard;
    int kiek_zuv;
    char pavadinimas[20];
    string pavad[5];
    int gramai[5];
    char zuvis[20];
    string zuv;
    int taskai;
    int bendra_suma;
    int g_suma;
};

void skaityti(eilute sarasas[], int &n, eilute zuviu_sarasas[], eilute naujas_sarasas[], int &m);
void skaiciuoti(eilute sarasas[], int n, eilute zuviu_sarasas[], int m);
void burbulas(eilute sarasas[], int &n);
void gramu_suma(eilute sarasas[], int n, eilute naujas_sarasas[], int m);
void burbulas1(eilute naujas_sarasas[], int m);

int main()
{
    eilute sarasas[100], zuviu_sarasas[100], naujas_sarasas[100];
    int n, m;
    skaityti(sarasas, n, zuviu_sarasas, naujas_sarasas, m);
    skaiciuoti(sarasas, n, zuviu_sarasas, m);
    burbulas(sarasas, n);
    cout << "Dalyviai" << endl;
    forLoop(i, n)
    {
        cout << sarasas[i].vard << " " << sarasas[i].bendra_suma << endl;
    }
    gramu_suma(sarasas, n, naujas_sarasas, m);
    burbulas1(naujas_sarasas, m);
    cout << "Laimikis" << endl;
    forLoop(k, m)
    {
        cout << naujas_sarasas[k].zuv << " " << naujas_sarasas[k].g_suma << endl;
    }
    return 0;
}

//=========================================

void skaityti(eilute sarasas[], int &n, eilute zuviu_sarasas[], eilute naujas_sarasas[], int &m)
{
    ifstream f1("U1.txt");
    f1 >> n;
    forLoop(i, n)
    {
        f1.ignore();
        f1.get(sarasas[i].vardas, 20);
        sarasas[i].vard = sarasas[i].vardas;
        f1 >> sarasas[i].kiek_zuv;
        forLoop(j, sarasas[i].kiek_zuv)
        {
            f1.ignore();
            f1.get(sarasas[i].pavadinimas, 20);
            sarasas[i].pavad[j] = sarasas[i].pavadinimas;
            f1 >> sarasas[i].gramai[j];
        }
    }
    f1 >> m;
    forLoop(i, m)
    {
        f1.ignore();
        f1.get(zuviu_sarasas[i].zuvis, 20);
        zuviu_sarasas[i].zuv = zuviu_sarasas[i].zuvis;
        f1 >> zuviu_sarasas[i].taskai;
    }
    forLoop(i, m)
    {
        naujas_sarasas[i].zuv = zuviu_sarasas[i].zuv;
        naujas_sarasas[i].g_suma = 0;
    }
    f1.close();
}

//=========================================

void skaiciuoti(eilute sarasas[], int n, eilute zuviu_sarasas[], int m)
{
    forLoop(i, n)
    {
        forLoop(j, sarasas[i].kiek_zuv)
        {
            forLoop(k, m)
            {
                int x = 0;
                if(sarasas[i].pavad[j] == zuviu_sarasas[k].zuv)
                {
                    if(sarasas[i].gramai[j] < 200)
                    {
                        x = zuviu_sarasas[k].taskai + maz;
                    }
                    else
                    {
                        x = zuviu_sarasas[k].taskai + did;
                    }
                    sarasas[i].bendra_suma += x;
                }
            }
        }
    }
}

//=========================================

void burbulas(eilute sarasas[], int &n)
{
    forLoop(i, n - 1)
    {
        forLoop(j, n - 1)
        {
            if(sarasas[j].bendra_suma < sarasas[j + 1].bendra_suma)
            {
                swap(sarasas[j], sarasas[j + 1]);
            }
        }
    }
}

//========================================

void gramu_suma(eilute sarasas[], int n, eilute naujas_sarasas[], int m)
{
    forLoop(i, n)
    {
        forLoop(j, sarasas[i].kiek_zuv)
        {
            forLoop(k, m)
            {
                if(sarasas[i].pavad[j] == naujas_sarasas[k].zuv)
                {
                    naujas_sarasas[k].g_suma += sarasas[i].gramai[j];
                }
            }
        }
    }
}

//=========================================

void burbulas1(eilute naujas_sarasas[], int m)
{
    forLoop(i, m - 1)
    {
        forLoop(j, m - 1)
        {
            if(naujas_sarasas[j].zuv < naujas_sarasas[j + 1].zuv)
            {
                swap(naujas_sarasas[j], naujas_sarasas[j + 1]);
            }
        }
    }
}
