#include <iostream>
#include <fstream>

using namespace std;

struct eilute
{
    char var[20];
    string vardas;
    string klas;
    int kiekis;
    int balai[100];
    float vidur;
};

void skaityti(eilute sarasas[], int &n);
void skaiciuoti(eilute sarasas[], eilute nauj_sarasas[], int n, int &index);
void vidurkis(eilute sarasas[], eilute nauj_sarasas[], int n, int index);
void rasyti(eilute sarasas[], eilute nauj_sarasas[], int n, int index);

int main()
{
    eilute sarasas[100], nauj_sarasas[100];
    int n, index;
    skaityti(sarasas, n);
    skaiciuoti(sarasas, nauj_sarasas, n, index);
    vidurkis(sarasas, nauj_sarasas, n, index);
    rasyti(sarasas, nauj_sarasas, n, index);
    return 0;
}

//-----------------------------------------

void skaityti(eilute sarasas[], int &n)
{
    ifstream f1("in.txt");
    f1 >> n;
    for(int i = 0; i < n; i++)
    {
        f1.ignore();
        f1.get(sarasas[i].var, 20);
        sarasas[i].vardas = sarasas[i].var;
        f1 >> sarasas[i].klas >> sarasas[i].kiekis;
        for(int j = 0; j < sarasas[i].kiekis; j++)
        {
            f1 >> sarasas[i].balai[j];
        }
    }
    f1.close();
}

//----------------------------------------------

void skaiciuoti(eilute sarasas[], eilute nauj_sarasas[], int n, int &index)
{
    index = 0;
    bool yra = 0;
    for(int i = 0; i < n; i++)
    {
        if(i == 0)
        {
            nauj_sarasas[0].klas = sarasas[0].klas;
            index++;
        }
        else
        {
            yra = 0;
            for(int j = 0; j < index; j++)
            {
                if(sarasas[i].klas == nauj_sarasas[j].klas)
                    yra = 1;
            }
            if(yra != 1)
            {
                nauj_sarasas[index].klas = sarasas[i].klas;
                index++;
            }
        }
    }
}

//-------------------------------------------

void vidurkis(eilute sarasas[], eilute nauj_sarasas[], int n, int index)
{
    for(int i = 0; i < n; i++)
    {
        int x = 0;
        for(int j = 0; j < sarasas[i].kiekis; j++)
        {
            x += sarasas[i].balai[j];
        }
        sarasas[i].vidur = x / (float) sarasas[i].kiekis;
        sarasas[i].vidur = floor(sarasas[i].vidur * 10 + 0.5) / 10;
    }
}

//----------------------------------------------------

void rasyti(eilute sarasas[], eilute nauj_sarasas[], int n, int index)
{
    ofstream f2("out.txt");
    for(int i = 0; i < index; i++)
    {
        f2 << "Klase " << nauj_sarasas[i].klas << ":" << endl;
        for(int j = 0; j < n; j++)
        {
            if(sarasas[j].klas == nauj_sarasas[i].klas)
            {
                f2 << sarasas[j].vardas << " " << sarasas[j].vidur << " " << (int) sarasas[j].vidur << endl;
            }
        }
        f2 << "\n";
    }

    double maziaus = sarasas[0].vidur;
    double didziaus = sarasas[0].vidur;
    for(int i = 0; i < n; i++)
    {
        if(didziaus < sarasas[i].vidur)
             didziaus = sarasas[i].vidur;
        if(maziaus > sarasas[i].vidur)
            maziaus = sarasas[i].vidur;
    }
    for(int i = 0; i < n; i++)
    {
        if(maziaus == sarasas[i].vidur)
            f2 << "Maziausias vidurkis: " << sarasas[i].vardas << " is " << sarasas[i].klas << endl;
        if(didziaus == sarasas[i].vidur)
            f2 << "Didziausias vidurkis: " << sarasas[i].vardas << " is " << sarasas[i].klas << endl;
    }
    f2.close();
}
