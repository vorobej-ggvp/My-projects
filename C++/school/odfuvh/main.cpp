#include <iostream>
using namespace std;

void newInitArray(float*, int);
void printArray(float*, int);
float sumConditionElements(float*, int);

int main() {
    int size;
    cout << "Input dimension" << endl;
    cin >> size;
    float* array = new float[size];
    newInitArray(array, size);
    cout << "Initialized array:\n" << endl;
    printArray(array, size);

    float sum = sumConditionElements(array, size);
        cout << "Sum of elements where index is greater than value: " << sum << endl;


    delete[] array;
    return 0;
}

void newInitArray(float* a, int n) {
    for (int i = 0; i < n; i++) {
        cout << " A[" << i << "] = ";
        cin >> a[i];
    }
}

void printArray(float* a, int n) {
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}

float sumConditionElements(float* a, int n) {
    float sum = 0;
    for (int i = 0; i < n; i++) {
        if (i > a[i]) {
            sum = sum + a[i];
        }
    }
    return sum;
}
