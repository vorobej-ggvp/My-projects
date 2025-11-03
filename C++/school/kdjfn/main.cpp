#include <iostream>

using namespace std;

int checking(int a, int y);

int main()
{
    int a, y;
    cout << "Input a: " << endl;
    cin >> a;
    cout << "\nResult of y: " << checking(a, y) << endl;
    return 0;
}

int checking(int a, int y)
{
    if(a % 7 == 0)
        return y = 200;
    else
        return y = 500;
}
