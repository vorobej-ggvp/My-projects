#include <iostream>
#include <locale.h>

using namespace std;

int main()
{
    setlocale(0, "Russian");
    float array[]{1., 21., 13., 64., 5.};
    int n{ sizeof(array) / sizeof(float) };

    cout << "Исходный массив: " << endl;
    for(int i(0); i < n; i++)
    {
        cout << " " << array[i];
    }

    /*float temp;
    for(int i = 0; i < n / 2; i++)
    {
        temp = array[i];
        array[i] = array[n - 1 - i];
        array[n - 1 - i] = temp;
    }
    cout << endl << "Массив после реверса" << endl;
    for(int i = 0; i < n; i++)
        cout << " " << array[i];
*/
    //------------------------

    //забой элемента [2]
    /*for(int i = 2; i < n - 1; i++)
    {
        array[i] = array[i + 1];
    }
    n -= 1;

    cout << endl << "Массив после забоя [2] = 13." << endl;
    for(int i = 0; i < n; i++)
        cout << " " << array[i];*/

    //------------------------
/*
    //сохранение значения array[0]
    float temp = array[0];
    //забой элемента array[0]
    for(int i = 0; i < n - 1; i++)
    {
        array[i] = array[i + 1];
    }
    array[n - 1] = temp;

    cout << endl << "Массив после циклического сдвига влево" << endl;
    for(int i = 0; i < n; i++)
        cout << " " << array[i];*/

    //---------------------------
/*
    //сохранение значения array[n - 1]
    float temp = array[n - 1];
    //забой элемента array[n - 1]
    for(int i = n - 1; i > 0; i--)
    {
        array[i] = array[i - 1];
    }
    array[0] = temp;

    cout << endl << "Массив после циклического сдвига вправо" << endl;
    for(int i = 0; i < n; i++)
        cout << " " << array[i];*/

    //--------------------------
/*
    for(int i = 0; i < n - 1; i++)
    {
        min = i;
        for(int j = i + 1; j < n; j++)
        {
            if(array[j] < array[min])
            {
                min = j;
            }
        }
        float temp(array[i]);
        array[i] = array[min];
        array[min] = temp;
    }

    cout << endl << "Массив после сортировки выбором" << endl;
    for(int i(0); i < n; i++)
        cout << " " << array[i];*/

    //------------------------------
/*
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        {
            if(array[j] > array[j + 1])
            {
                float temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }

    cout << endl << "Массив после сортировки пузырьком" << endl;
    for(int i(0); i < n; i++)
        cout << " " << array[i];*/
    return 0;
}
