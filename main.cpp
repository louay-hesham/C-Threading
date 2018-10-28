#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <pthread.h>
#include <unistd.h>
#include <chrono>
#include <future>


using namespace std;

int** readMatrix(int *n, int *m) {
    cin >> *n;
    cin >> *m;
    int **matrix = new int*[*n];

    for (int i = 0; i < *n; i++) {
        matrix[i] = new int[*m];
        for (int j = 0; j < *m; j++)
            cin >> matrix[i][j];
    }
    return matrix;
}

int** transpose(int n, int m, int** matrix) {
    int **matrixTransposed = new int*[m];
    for (int j = 0; j < m; j++) {
        matrixTransposed[j] = new int[n];
        for (int i = 0; i < n; i++) {
            matrixTransposed[j][i] = matrix[i][j];
        }
    }
    return matrixTransposed;
}

void compute_element(int n, int* row, int* column, int* result_location) {
    int element = 0;
    for (int i = 0; i < n; i++) {
        element += (row[i] * column[i]);
    }
    *result_location = element;
}

void matrixMultiplyElement(int n1, int m1, int** matrix1, int n2, int m2, int** matrix2) {
    int** matrix2_transposed = transpose(n2, m2, matrix2);
    int result_matrix[n1][m2];

    thread* threads[n1][m2];

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < m2; j++) {
            threads[i][j] = new thread(&compute_element, n2, matrix1[i], matrix2_transposed[j], &result_matrix[i][j]);
        }
    }

    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < m2; j++) {
            threads[i][j]->join();
        }
    }
    auto finish = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < m2; j++) {
            cout << result_matrix[i][j] << "\t";
        }
        cout << endl;
    }
    cout << "Time elapsed (each element in a thread): " << chrono::duration_cast<chrono::nanoseconds>(finish-start).count() << " nanoseconds." << endl;
}

void compute_row(int n, int m, int* row, int** matrix, int* result_row_location) {
    for (int i =0; i < m; i++) {
        compute_element(n, row, matrix[i], &result_row_location[i]);
    }
}

void matrixMultiplyRow(int n1, int m1, int** matrix1, int n2, int m2, int** matrix2) {
    int** matrix2_transposed = transpose(n2, m2, matrix2);
    int* result_matrix[n1];

    thread* threads[n1];

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n1; i++) {
        result_matrix[i] = new int[m2];
        threads[i] = new thread(&compute_row, n2, m2, matrix1[i], matrix2_transposed, result_matrix[i]);
    }

    for (int i =0; i < n1; i++) {
        threads[i]->join();
    }
    auto finish = std::chrono::high_resolution_clock::now();
    for (int i =0; i < n1; i++) {
        for (int j = 0; j < m2; j++) {
            cout << result_matrix[i][j] << "\t";
        }
        cout << endl;
    }
    cout << "Time elapsed (each row in a thread): " << chrono::duration_cast<chrono::nanoseconds>(finish-start).count() << " nanoseconds." << endl;
}

void matrixMultiply() {
    freopen("input.txt","r",stdin);
    int n1, m1;
    int** matrix1 = readMatrix(&n1, &m1);
    int n2, m2;
    int** matrix2 = readMatrix(&n2, &m2);
    freopen("output.txt", "w", stdout);
    matrixMultiplyElement(n1, m1, matrix1, n2, m2, matrix2);
    matrixMultiplyRow(n1, m1, matrix1, n2, m2, matrix2);
}

int *merge_ar(int n1, int* ar1, int n2, int* ar2) {
    int i = 0, j = 0, k = 0;
    int* sorted_array = (int*)malloc((n1 + n2) * sizeof(int));
    while ((i < n1) && (j < n2)) {
        if (ar1[i] < ar2[j]) {
            *(sorted_array + k) = ar1[i];
            i++;
        } else {
            *(sorted_array + k) = ar2[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        *(sorted_array + k) = ar1[i];
        i++;
        k++;
    }
    while (j < n2) {
        *(sorted_array + k) = ar2[j];
        j++;
        k++;
    }
    return sorted_array;
}


void sort_ar(int n, int* ar, promise<int*> && merged) {
    if (n == 1) {
        merged.set_value(ar);
        return;
    }
    int n1 = n / 2;
    int n2 = n - n1;
    promise<int*> p1, p2;
    auto f1 = p1.get_future();
    auto f2 = p2.get_future();
    thread* t1 = new thread(&sort_ar, n1, ar, move(p1));
    thread* t2 = new thread(&sort_ar, n2, ar + n1, move(p2));
    t1->join();
    t2->join();
    merged.set_value(merge_ar(n1, f1.get(), n2, f2.get()));
}

void mergeSort() {
    freopen("input.txt","r",stdin);
    int n;
    cin >> n;
    int* ar = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        cin >> ar[i];
    }
    auto start = std::chrono::high_resolution_clock::now();
    promise<int*> p;
    auto f = p.get_future();
    thread* t = new thread(&sort_ar, n, ar, move(p));
    t->join();
    int* sorted_ar = f.get();
    auto finish = std::chrono::high_resolution_clock::now();
    freopen("output.txt", "w", stdout);
    for(int i = 0; i < n; i++) {
        cout << sorted_ar[i] << "\t";
    }
    cout << endl << "Time elapsed: " << chrono::duration_cast<chrono::nanoseconds>(finish-start).count() << " nanoseconds" << endl;
}

int main() {
    cout << "Choose option:" << endl;
    cout << "1- Matrix multiplication" << endl;
    cout << "2- Merge sort" << endl;
    int choice = -1;
    cin >> choice;
    switch(choice) {
    case 1:
        matrixMultiply();
        break;
    case 2:
        mergeSort();
        break;
    default:
        cout << "Incorrect option" << endl;
    }
    return 0;
}
