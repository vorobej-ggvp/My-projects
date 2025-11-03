#include <iostream>
#include <fstream>

using namespace std;

void skaityti(int &a, int &b, int mas1[], int mas2[], int mas3[]);
char skaicuoti1(int sk);
char skaicuoti2(int sk);

int main()
{
    int a, b, mas1[6], mas2[6], mas3[6], x, y, n = 0;
    skaityti(a, b, mas1, mas2, mas3);
    for(int i = 0; i < a; i++)
    {
        for(int j = 0; j < b; j++)
        {
            cout << skaicuoti1(mas1[n]) << skaicuoti2(mas1[n]) << skaicuoti1(mas2[n]) << skaicuoti2(mas2[n]) << skaicuoti1(mas3[n]) << skaicuoti2(mas3[n]) << ";";
            n++;
        }
        cout << endl;
    }
    cout << 1;
    return 0;
}

//--------------------------

void skaityti(int &a, int &b, int mas1[], int mas2[], int mas3[])
{
    ifstream f1("in.txt");
    f1 >> a >> b;
    for(int i = 0; i < a * b; i++)
    {
        f1 >> mas1[i] >> mas2[i] >> mas3[i];
    }
    f1.close();
}

//----------------------------------

char skaicuoti1(int sk)
{
    char mas[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    return mas[sk / 16];
}

char skaicuoti2(int sk)
{
    char mas[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    return mas[sk % 16];
}
