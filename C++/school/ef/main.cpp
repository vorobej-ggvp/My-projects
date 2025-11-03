#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct eilute1
{
    string kodas;
    double rezultatas;
};

struct eilute2
{
    string vardas;
    double maximum;
    int data;
    string valstybe;
};

void skaityti1(eilute1 sarasas[], int &n);
void skaityti2(eilute2 sarasas1[], int &n);

double vidur(eilute1 sarasas[], int n);
double skirtumas(eilute1 sarasas[], int n);

double vidur1(eilute2 sarasas1[], int n);
double vidurkis(double vidDid, double vidDisk);

void salintiVar(eilute2 sarasas1[], int n);
int salintiData(eilute2 sarasas1[], int i);
string sena(string dat[], int n);
int Sena(eilute2 sarasas1[], int n);

double skirtMax(eilute2 sarasas1[], eilute1 sarasas[], int i);

void burbulas(double skirt[], eilute2 sarasas1[], int &n);

int main()
{
    eilute1 sarasas[100];
    eilute2 sarasas1[100];
    int n, dat[100];
    string h;
    double vidDisk, vidDid, skirt[100];
    skaityti1(sarasas, n);
    skaityti2(sarasas1, n);

    cout << "Disko metimo duomenu analizes rezultatai:" << endl;

    cout << "Olimpines zaidynós:" << endl;
    cout << "Vidutiniskai diskas skriejo " << vidur(sarasas, n) << " m." << endl;
    vidDisk = vidur(sarasas, n);
    cout << "Skirtumas tarp didziausio ir maziausio rezultato " << skirtumas(sarasas, n) << " m." << endl;

    cout << "Geriausi rezultatai:" << endl;
    cout << "Vidutiniskai diskas skriejo " << vidur1(sarasas1, n) << " m." << endl;
    vidDid = vidur1(sarasas1, n);
    cout << "Vidurkis " << vidurkis(vidDid, vidDisk) << " m didesnis negu olimpinese zaidynese." << endl;

    cout << "Seniausiai pasiektas geriausias rezultatas:\n";
    salintiVar(sarasas1, n);
    for(int i = 0; i < n; i++)
    {
        dat[i] = salintiData(sarasas1, i);
    }
    cout << sarasas1[Sena(sarasas1, n)].vardas << " " << sarasas1[Sena(sarasas1, n)].maximum << " " << dat[Sena(sarasas1, n)] << " " << sarasas1[Sena(sarasas1, n)].valstybe << endl;

    cout << "Skirtumas tarp sportininku pasiekimu:" << endl;
    for(int i = 0; i < n; i++)
    {
        skirt[i] = skirtMax(sarasas1, sarasas, i);
    }
    burbulas(skirt, sarasas1, n);
    for(int i = 0; i < n; i++)
    {
        cout << sarasas1[i].vardas << " " << skirt[i] << " m" << endl;
    }
    return 0;
}

//-------------------------------------------------

void skaityti1(eilute1 sarasas[], int &n)
{
    ifstream f1("in1.txt");
    f1 >> n;
    for(int i = 0; i < n; i++)
    {
        f1 >> sarasas[i].kodas >> sarasas[i].rezultatas;
    }
    f1.close();
}

double vidur(eilute1 sarasas[], int n)
{
    double sum = 0;
    for(int i = 0; i < n; i++)
    {
        sum += sarasas[i].rezultatas;
    }
    return sum / n;
}

double skirtumas(eilute1 sarasas[], int n)
{
    double max1 = sarasas[0].rezultatas, min1 = sarasas[0].rezultatas;
    for(int i = 0; i < n; i++)
    {
        if(max1 < sarasas[i].rezultatas)
            max1 = sarasas[i].rezultatas;
        if(min1 > sarasas[i].rezultatas)
            min1 = sarasas[i].rezultatas;
    }
    return max1 - min1;
}

//============================================

void skaityti2(eilute2 sarasas1[], int &n)
{
    ifstream f2("in2.txt");
    for(int i = 0; i < n; i++)
    {
        f2 >> sarasas1[i].vardas >> sarasas1[i].maximum >> sarasas1[i].data >> sarasas1[i].valstybe;
    }
    f2.close();
}

double vidur1(eilute2 sarasas1[], int n)
{
    double sum = 0;
    for(int i = 0; i < n; i++)
    {
        sum += sarasas1[i].maximum;
    }
    return sum / n;
}

double vidurkis(double vidDid, double vidDisk)
{
    return vidDid - vidDisk;
}

//============================================

void salintiVar(eilute2 sarasas1[], int n)
{
    int kiekis[100];
    for(int i = 0; i < n; i++)
    {
        kiekis[i] = sarasas1[i].vardas.size();
    }
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < kiekis[i]; j++)
        {
            sarasas1[i].vardas[j] = sarasas1[i].vardas[j + 1];
        }
    }
}

int salintiData(eilute2 sarasas1[], int i)
{
    int rezult = sarasas1[i].data / 10000;
    return rezult;
}

string sena(string dat[], int n)
{
    for(int i = 0; i < n; i++)
    {
        if(i != n - 1)
            if(dat[i] < dat[i + 1])
                return dat[i];
    }
}

int Sena(eilute2 sarasas1[], int n)
{
    int rez = sarasas1[0].data;
    int index = 0;
    for(int j = 0; j < n; j++)
        if(sarasas1[j].data < rez)
        {
            rez = sarasas1[j].data;
            index = j;
        }
    return index;
}

//===============================================

double skirtMax(eilute2 sarasas1[], eilute1 sarasas[], int i)
{
    return sarasas1[i].maximum - sarasas[i].rezultatas;
}
 //==============================================

 void burbulas(double skirt[], eilute2 sarasas1[], int &n)
 {
     for(int k = 0; k < n - 1; k++)
        for(int i = 0; i < n - 1; i++)
        {
            if(skirt[i] > skirt[i + 1])
            {
                swap(skirt[i], skirt[i + 1]);
                swap(sarasas1[i], sarasas1[i + 1]);
            }
        }
 }
