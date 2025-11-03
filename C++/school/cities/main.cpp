#include <iostream>
#include <fstream>

using namespace std;

struct eilute
{
    char mies[20];
    char apsk[13];
    string miestai;
    string apskritys;
    int gyven;
    int kiek_apsk;
    int min_mies = 0;
    int sum = 0;
};

void skaityti(eilute sarasas[], int &n);
void skaiciuoti_apsk(eilute sarasas[], eilute nauj_sarasas[], int n, int &index);
void min_miestai(eilute sarasas[], eilute nauj_sarasas[], int n, int index);
void suma(eilute sarasas[], eilute nauj_sarasas[], int n, int index);

int main()
{
    eilute sarasas[110], nauj_sarasas[110];
    int n, index;
    int t = 0;
    skaityti(sarasas, n);
    skaiciuoti_apsk(sarasas, nauj_sarasas, n, index);
    min_miestai(sarasas, nauj_sarasas, n, index);
    suma(sarasas, nauj_sarasas, n, index);

    cout << index << endl;
    for(int i = 0; i < index; i++)
    {
        cout << nauj_sarasas[i].apskritys << " " << nauj_sarasas[i].min_mies << " " << nauj_sarasas[i].sum << endl;
    }
    return 0;
}

//=====================================

void skaityti(eilute sarasas[], int &n)
{
    ifstream f1("in.txt");
    f1 >> n;
    for(int i = 0; i < n; i++)
    {
        f1.ignore();
        f1.get(sarasas[i].mies, 20);
        sarasas[i].miestai = sarasas[i].mies;
        f1.ignore();
        f1.get(sarasas[i].apsk, 13);
        sarasas[i].apskritys = sarasas[i].apsk;
        f1 >> sarasas[i].gyven;
    }
    f1.close();
}

//====================================

void skaiciuoti_apsk(eilute sarasas[], eilute nauj_sarasas[], int n, int &index)
{
    index = 0;
    bool yra = 0;
    for(int i = 0; i < n; i++)
    {
        if(i == 0)
        {
            nauj_sarasas[0].apskritys = sarasas[0].apskritys;
            index++;
        }
        else
        {
            yra = 0;
            for(int j = 0; j < index; j++)
            {
                if(sarasas[i].apskritys == nauj_sarasas[j].apskritys)
                {
                    yra = 1;
                }
            }
            if(yra != 1)
            {
                nauj_sarasas[index].apskritys = sarasas[i].apskritys;
                index++;
            }
        }
    }
}

//===============================================

void min_miestai(eilute sarasas[], eilute nauj_sarasas[], int n, int index)
{
    for(int j = 0; j < index; j++)
    {
        for(int i = 0; i < n; i++)
        {
            if(i == 0)
            {
                nauj_sarasas[j].min_mies = sarasas[0].gyven;
            }
            if(nauj_sarasas[j].apskritys == sarasas[i].apskritys && sarasas[i].gyven < nauj_sarasas[j].min_mies && i != 0)
            {
                nauj_sarasas[j].min_mies = sarasas[i].gyven;
            }
        }
    }
    for(int k = 0; k < index - 1; k++)
    {
        for(int i = 0; i < index - 1; i++)
        {
            if(nauj_sarasas[i].min_mies > nauj_sarasas[i + 1].min_mies)
                swap(nauj_sarasas[i], nauj_sarasas[i + 1]);
        }
    }
}

//=================================================

void suma(eilute sarasas[], eilute nauj_sarasas[], int n, int index)
{
    for(int j = 0; j < index; j++)
    {
        for(int i = 0; i < n; i++)
        {
            if(nauj_sarasas[j].apskritys == sarasas[i].apskritys)
                nauj_sarasas[j].sum += sarasas[i].gyven;
        }
    }
}
