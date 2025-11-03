#include <iostream>

using namespace std;

int main()
{
    int n, m, d, k = 0;
    cin >> n >> m >> d;
    if (n % 2 == 0)
    {
        if(m >= d + 1)
        {
            k = n - m;
            cout << k;
        }
    }
    else
    {
        if(m >= d + 1)
        {
            k = n - m - 1;
            cout << k;
        }
    }
    return 0;
}
