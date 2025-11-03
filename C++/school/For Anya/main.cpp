#include <iostream>
#include <cmath>

using namespace std;

int forNumber(int a, int b);

int main()
{
    int a, b;

    while(true)
    {
        cout << "Input a, b" << endl;
        cin >> a >> b;
        if(0 < a && a < b)
            break;
        cout << "\nIncorrect input values " << endl;
    }
    cout << "Result with for = " << forNumber(a, b) << endl;
    return 0;
}

//===============================

int forNumber(int a, int b)
{
    int n = 0;
    double x;
    for(int i = a; i <= b; i++)
    {
        x = pow(i, (1.0 / 3));
        if((int) x % 2 == 1)
            n = n + ((x - (int) x) == 0);
    }
    return n;
}
