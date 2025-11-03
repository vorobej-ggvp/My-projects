#include <iostream>

using namespace std;

int main()
{
    int i = 0, i2 = 0, n = 0, n2 = 0, c = 0, d = 0;
    cin >> i;
    cin >> i2;
    int a[i][i2];
    for(int b = 0; b <= i - 1; b++){
        for(int b2 = 0; b2 <= i2 - 1; b2++){
            cin >> a[b][b2];
        }
    }
    for(int b = 0; b <= i - 1; b++){
        for(int b2 = 0; b2 <= i2 - 1; b2++)
        {
            c += a[b][b2];
        }
        cout << c << " ";
        c = 0;
    }
    cout << endl;
    for(int b2 = 0; b2 <= i2 - 1; b2++){
        for(int b = 0; b <= i - 1; b++)
        {
            d += a[b][b2];
        }
        cout << d << " ";
        d = 0;
    }
    cout << endl;
    cout << endl;
    for(int b = 0; b <= i - 1; b++){
        for(int b2 = 0; b2 <= i2 - 1; b2++)
        {
           cout << a[b][b2] << " ";
        }
        cout << endl;
    }
    return 0;
}
