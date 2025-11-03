#include <iostream>
#include <cmath>

using namespace std;

bool belongsArea(float, float, float);

int main()
{
    float RADIUS, xPoint, yPoint;
    cout << "x: ";
    cin >> xPoint;
    cout << "\ny: ";
    cin >> yPoint;
    cout << "\nRadius: ";
    cin >> RADIUS;
    if(belongsArea(xPoint, yPoint, RADIUS))
    {
        cout << "\nOK" << endl;
    }
    else
    {
        cout << "Missing" << endl;
    }
    return 0;
}

bool belongsArea(float x, float y, float r)
{
    return x * x + y * y <= pow(r, 2) && y < asin(-(sqrt(2)/2));;
}
