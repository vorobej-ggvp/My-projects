#include <iostream>
#include <fstream>

using namespace std;

struct eilute
{
    int kiek;
    string sport[100];
    string kada[100];
    int minut[100];
};

void skaityti(eilute sarasas[], int &n);
void skaicuoti_pratimo(eilute sarasas[], eilute nauj_sarasas[], int n, int &index);

int main()
{
    eilute sarasas[100], nauj_sarasas[100];
    int n, index;
    skaityti(sarasas, n);
    skaicuoti_pratimo(sarasas, nauj_sarasas, n, index);
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < sarasas[i].kiek; j++)
        {
            cout << nauj_sarasas[i].sport[j];/* << " " << sarasas[i].kada[j] << " " << sarasas[i].minut[j] << " ";*/
        }
        cout << endl;
    }
    return 0;
}

//=================================================

void skaityti(eilute sarasas[], int &n)
{
    ifstream f1("in.txt");
    f1 >> n;
    for(int i = 0; i < n; i++)
    {
        f1 >> sarasas[i].kiek;
        for(int j = 0; j < sarasas[i].kiek; j++)
        {
            f1 >> sarasas[i].sport[j] >> sarasas[i].kada[j] >> sarasas[i].minut[j];
        }
    }
}

//======================================================

void skaicuoti_pratimo(eilute sarasas[], eilute nauj_sarasas[], int n, int &index)
{
    index = 0;
    bool yra = 0;
    for(int i = 0; i < n; i++)
    {
        if(i == 0)
        {
            nauj_sarasas[0].sport[0] = sarasas[0].sport[0];
            index++;
        }
        else
        {
            for(int k = 0; k < sarasas[i].kiek; k++)
            {
                yra = 0;
                for(int j = 0 ; j < index; j++)
                {
                    if(sarasas[i].sport[k] == nauj_sarasas[i].sport[j])
                        yra = 1;
                }
                if(yra != 1)
                {
                    nauj_sarasas[i].sport[index] = sarasas[i].sport[k];
                    index++;
                }
            }
        }
    }
}
