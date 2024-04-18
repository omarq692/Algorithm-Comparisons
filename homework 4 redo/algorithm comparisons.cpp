#include <iostream>
#include <chrono>
using namespace std;

void bubbleSort(int arr[], int n);
void insertionSort(int arr[], int n);
void merge(int arr[], int l, int m, int r);
void mergeSort(int arr[], int l, int r);
void benchmarkSort(void (*sortFunction)(int[], int), int arr[], int size, const string& name);
void benchmarkSort(void (*sortFunction)(int[], int, int), int arr[], int size, const string& name);
// Bubble Sort implementation
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
    }
}
// Insertion Sort implementation
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
// Merge Sort implementation
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int* L = new int[n1];
    int* R = new int[n2];
    for (int i = 0; i < n1; ++i)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[m + 1 + j];
    int i = 0;
    int j = 0;
    int k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            ++i;
        }
        else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }
    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }
    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }
    delete[] L;
    delete[] R;
}
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// benchmark sorting algorithm (bubble, insertion, and merge)
void benchmarkSort(void (*sortFunction)(int[], int), int arr[], int size, const string& name) {
    auto start = chrono::high_resolution_clock::now();
    sortFunction(arr, size);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_seconds = end - start;
    cout << name << " Time for size " << size << ": " << elapsed_seconds.count() << "s\n";
}

// sorting algorithm (merge)
void benchmarkSort(void (*sortFunction)(int[], int, int), int arr[], int size, const string& name) {
    auto start = chrono::high_resolution_clock::now();
    sortFunction(arr, 0, size - 1);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_seconds = end - start;
    cout << name << " Time for size " << size << ": " << elapsed_seconds.count() << "s\n";
}

int main() {
    const int sizes[] = { 10, 100, 1000, 10000 };
    for (int size : sizes) {
        int* arr = new int[size];
        for (int i = 0; i < size; ++i) {
            arr[i] = i + 1;
        }
        benchmarkSort(bubbleSort, arr, size, "Bubble Sort");
        for (int i = 0; i < size; ++i) {
            arr[i] = i + 1;
        }
        benchmarkSort(insertionSort, arr, size, "Insertion Sort"); // Measure insertion sort
        for (int i = 0; i < size; ++i) {
            arr[i] = i + 1;
        }
        benchmarkSort(mergeSort, arr, size, "Merge Sort");
        delete[] arr;
    }
    return 0;
}
