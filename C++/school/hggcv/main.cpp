#include <iostream>
using namespace std;

int main() {
    int r;
    cin >> r;
    double d = r / 2; cout << d * 1.0 << endl;
    cout << "Užbrūkšniuotas plotas " << (double)r * r - d * 1.0 * d * 1.0 * 3.14 << endl;
    return 0;
}
