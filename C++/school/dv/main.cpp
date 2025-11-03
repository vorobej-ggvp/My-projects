#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream f1 ("in.txt");
    int n;
    f1 >> n;
    cout << n;
    return 0;
}
