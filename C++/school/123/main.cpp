#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    int n, mid, sum = 0, k = 0, maks = 0;
    double f;
    ifstream f1 ("in.txt");
    ofstream f2 ("out.txt");
    f1 >> n;
    for(int i = 0; i < n; i++)
    {
        f1 >> mid;
        if(mid < 5)
        {
            k++;
            sum += mid;
        }
        if(mid > 5)
            maks = mid;
    }
    f = sum / k;
    f1.close();
    f2 << "Arithm mean: " << f << "\n" << "Max num: " << maks;
    return 0;
}
