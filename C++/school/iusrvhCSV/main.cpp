#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

struct eilute
{
    string marke;
    string modelis;
    int metai;
    int kaina;
    int rida;
};

void skaityti(eilute viskas, vector<eilute> &mas, string &line, string &z, string &x, string &c, string &v, string &b);

int main()
{
    string z, x, c, v, b;
    eilute viskas;
    vector <eilute> mas;
    string line;
    skaityti(viskas, mas, line, z, x, c, v, b);
    cout << z << " " << x << " " << c << " " << v << " " << b << " ";
    for(int i = 0; i < mas.size(); i++)
    {
        cout << mas[i].marke << " " << mas[i].modelis << " " << mas[i].metai << " " << mas[i].kaina << " " << mas[i].rida << endl;
    }
    return 0;
}

//---------------------------------------

void skaityti(eilute viskas, vector<eilute> &mas, string &line, string &z, string &x, string &c, string &v, string &b)
{
    ifstream f1("in.txt");
    f1 >> z;
    f1.ignore(1, ';');
    f1 >> x;
    f1.ignore(1, ';');
    f1 >> c;
    f1.ignore(1, ';');
    f1 >> v;
    f1.ignore(1, ';');
    f1 >> b;
    f1.ignore(1, ';');
    while(getline(f1, line))
    {
        stringstream ss(line);
        getline(ss, viskas.marke, ';');
        getline(ss, viskas.modelis, ';');
        ss >> viskas.metai;
        ss.ignore(1, ';');
        ss >> viskas.kaina;
        ss.ignore(1, ';');
        ss >> viskas.rida;
        ss.ignore(1, ';');
        mas.push_back(viskas);
    }
    f1.close();
}
