#include <iostream>

using namespace std;

int main()
{
    double a1, b1, c1, a2, b2, c2, n, m;
    cin >> a1 >> b1 >> c1 >> a2 >> b2 >> c2;
    n = a1 * b1 * c1;
    m = a2 * b2 * c2;
    if (n == m)
        cout << "Boxes are equal";
    else if (n > m)
        cout << "The first box is larger than the second one";
        else if (n < m)
        cout << "The first box is smaller than the second one";
            else
            cout << "Boxes are incomparable";
    return 0;
}
