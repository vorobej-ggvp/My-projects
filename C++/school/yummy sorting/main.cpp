#include <iostream>
#include <locale.h>
//random numbers rand() & srand()
#include <cstdlib>
//take our time time()
#include <ctime>
//macros:
//macro const - MACRO_NAME value
#define N 100
#define MAX_RAND 100
//macro expression - MACRO_NAME (expression within brackets) or MACRO_NAME(parameters) (expression)
#define forLoop(len) for(int i = 0; i < len; i++)

using namespace std;

void initArray(double (&)[N], int);
void printArray(double (&)[N], int);
void reverseArray(double (&)[N], int);

void cyclicLeftShift(double*, int);
void selectionArray(double*, int n);

int main()
{
    setlocale(0, "Russian");
    double array[N];
    int n = 10;

    /*while(true)
    {
        cout << "Введите число элементов <= " << N << endl;
        cin >> n;
        if(0 < n && n <= N)
            break;
    }*/

    initArray(array, n);

    cout << "Псевдо случ. массив" << endl;
    printArray(array, n);

    reverseArray(array, n);
    cout << endl << "Массив после реверса" << endl;
    printArray(array, n);

    /*cyclicLeftShift(array, n);
    cout << endl << "Массив после цикл. сдвига" << endl;
    printArray(array, n);

    selectionArray(array, n);
    cout << endl << "Отсортированный массив" << endl;
    printArray(array, n);
*/
    return 0;
}

//----------------------------

void initArray(double (&a)[N], int n)
{
    srand(time(0));
    forLoop(n)
    {
        a[i] = (rand() % MAX_RAND) * 0.1;
    }
}

void printArray(double (&a)[N], int n)
{
    forLoop(n)
    {
        cout << " " << a[i];
    }
}

void reverseArray(double (&a)[N], int n)
{
    double temp;
    for(int i = 0; i < n / 2; i++)
    {
        temp = a[i];
        a[i] = a[(n - i - 1) / 2];
        a[(n - i - 1) / 2] = temp;
    }
}

void cyclicLeftShift(double* a, int n)
{
    double temp = a[0];
    for(int i = 0; i < n - 1; i++)
    {
        a[i] = a[i + 1];
    }
    a[n - 1] = temp;
}

void selectionArray(double* a, int n)
{
    float temp;
    for(int i = 0; i < n - 1; i++)
    {
        int min = i;
        for(int j = i + 1; j < n; j++)
        {
            if(a[j] < a[min])
                min = j;
        }
        temp = a[i];
        a[i] = a[min];
        a[min] = temp;
    }
}
