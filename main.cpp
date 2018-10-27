#include <iostream>
#include <cstdio>

using namespace std;

int** readMatrix(int *n, int *m) {
    cin >> *n;
    cin >> *m;
    int **matrix;

    for (int i = 0; i < *n; i++) {
        matrix[i] = new int[*m];
        for (int j = 0; j < *m; j++)
            cin >> matrix[i][j];
    }
    return matrix;
}

void matrixMultiplyElement(int n1, int m1, int** matrix1, int n2, int m2, int** matrix2) {

}

void matrixMultiplyRow() {

}

void matrixMultiply() {
    freopen("input.txt","r",stdin);
    int n1, m1;
    int** matrix1 = readMatrix(&n1, &m1);
    int n2, m2;
    int** matrix2 = readMatrix(&n2, &m2);
    matrixMultiplyElement(n1, m1, matrix1, n2, m2, matrix2);
    matrixMultiplyRow();
}

void mergeSort() {

}

int main() {
    while (1) {
        cout << "Choose option:" << endl;
        cout << "1- Matrix multiplication" << endl;
        cout << "2- Merge sort" << endl;
        cout << "0- Exit" << endl;
        int choice = -1;
        cin >> choice;
        switch(choice) {
        case 0:
            return 0;
        case 1:
            matrixMultiply();
            break;
        case 2:
            mergeSort();
            break;
        default:
            cout << "Incorrect option" << endl;
        }
    }
    return 0;
}
