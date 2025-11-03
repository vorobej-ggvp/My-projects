#include <iostream>
#include <cmath>

using namespace std;

enum set
{
    NOTHING,
    FIRST_SET,
    SECOND_SET,
    THIRD_SET
};

set detectorSet(double aValue, double xValue)
{
    if(-8 <= (aValue * xValue) && (aValue * xValue) <= -3 || 0 <= (aValue * xValue) && (aValue * xValue) <= 4)
        return FIRST_SET;
    if(-3 < (aValue * xValue) && (aValue * xValue) < 0)
        return SECOND_SET;
    if((aValue * xValue) < -8 || (aValue * xValue) > 4)
        return THIRD_SET;
    return NOTHING;
}

int main()
{
    cout << "a: ";
    double a;
    cin >> a;
    cout << "\nx: ";
    double x;
    cin >> x;
    switch(detectorSet(a, x))
    {
        case FIRST_SET: cout << "√(a^2 * |cos(x)|) = " << sqrt((a * a) * fabs(cos(x))) << endl;
                        break;
        case SECOND_SET: cout << "a^2 * cos(x^2) + 1 = " << a * a * cos(x * x) + 1 << endl;
                        break;
        case THIRD_SET: cout << "ln(|a^2 + x|) = " << log(fabs(a * a + x)) << endl;
        default: cout << "Print error" << endl;
    }
    return 0;
}
