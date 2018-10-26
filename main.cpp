#include <iostream>

using namespace std;

void matrixMultiplyElement() {

}

void matrixMultiplyRow() {

}

void mergeSort() {

}

int main() {
    while (1) {
        cout << "Choose option:" << endl;
        cout << "1- Matrix multiplication (one element per thread)" << endl;
        cout << "2- Matrix multiplication (one row per thread)" << endl;
        cout << "3- Merge sort" << endl;
        cout << "0- Exit" << endl;
        int choice = -1;
        cin >> choice;
        switch(choice) {
        case 0:
            return 0;
        case 1:
            matrixMultiplyElement();
        case 2:
            matrixMultiplyRow();
        case 3:
            mergeSort();
        default:
            cout << "Incorrect option" << endl;
        }
    }
    return 0;
}
