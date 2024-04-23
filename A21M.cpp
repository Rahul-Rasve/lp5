#include <bits/stdc++.h>
#include <ctime>
#include <omp.h>

using namespace std;

// Function to generate array with random numbers
vector<int> generateRandomArray(int n) {
    vector<int> arr(n);
    srand(time(0)); // Seed for random number generation

    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100; // Generate random numbers between 0 and 99
    }

    return arr;
}

// Function to merge two halves of the array
void merge(vector<int>& arr, int l, int m, int r) {
    vector<int> temp(r - l + 1);
    int i = l, j = m + 1, k = 0;

    while (i <= m && j <= r) {
        if (arr[i] < arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= m) {
        temp[k++] = arr[i++];
    }

    while (j <= r) {
        temp[k++] = arr[j++];
    }

    #pragma omp parallel for
    for (int i = l; i <= r; i++) {
        arr[i] = temp[i - l];
    }
}

// Function to perform sequential merge sort
void sequentialMergeSort(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        sequentialMergeSort(arr, l, m);
        sequentialMergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Function to perform parallel merge sort
void parallelMergeSort(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            parallelMergeSort(arr, l, m);

            #pragma omp section
            parallelMergeSort(arr, m + 1, r);
        }

        merge(arr, l, m, r);
    }
}

// Function to compute sorting time
void computeSortingTime(void (*sortFunction)(vector<int>&, int, int), int n, string msg) {
    // Generate array
    vector<int> arr = generateRandomArray(n);

    // Record start and end time
    clock_t startTime = clock();
    sortFunction(arr, 0, n - 1);
    clock_t endTime = clock();

    double timeTaken = double(endTime - startTime) / CLOCKS_PER_SEC;

    cout << msg << timeTaken << " seconds" << endl;
}

// Function to print the array
void printArray(vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int n;
    cout << "Enter the size of the array: ";
    cin >> n;

    cout<<"\nSeguential Merge Sort=>"<<endl;
    computeSortingTime(sequentialMergeSort, n, "Time taken by Sequential Merge Sort: ");

    cout<<"\nParallel Merge Sort=>"<<endl;
    computeSortingTime(parallelMergeSort, n, "Time taken by Parallel Merge Sort: ");

    return 0;
}