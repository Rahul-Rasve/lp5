#include <bits/stdc++.h>
#include <omp.h>
#include <ctime>

using namespace std;

// Function to generate an array with random numbers
vector<int> generateRandomArray(int n) {
    vector<int> arr(n);
    srand(time(0)); // Seed for random number generation

    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100; // Generate random numbers between 0 and 99
    }

    return arr;
}

// Function to perform sequential bubble sort
void sequentialBubbleSort(vector<int>& arr, int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Function to perform parallel bubble sort
void parallelBubbleSort(vector<int>& arr, int n) {
    #pragma omp parallel for shared(arr)
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; j += 2) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Function to print the array
void printArray(vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Function to compute sorting time
void computeSortingTime(void (*sortFunction)(vector<int>&, int), int n, string msg) {
    //generate array
    vector<int> arr = generateRandomArray(n);

    //record start and end time
    clock_t startTime = clock();
    sortFunction(arr, n);
    clock_t endTime = clock();
    double timeTaken = double(endTime - startTime) / CLOCKS_PER_SEC;
    cout << msg << timeTaken << " seconds" << endl;
}

int main() {
    int n;
    cout << "Enter the size of the array: ";
    cin >> n;
    
    cout << "\nSequential Bubble Sort=>" << endl;
    computeSortingTime(sequentialBubbleSort, n, "Time taken by Sequential Bubble Sort: ");

    cout << "\nParallel Bubble Sort=>" << endl;
    computeSortingTime(parallelBubbleSort, n, "Time taken by Parallel Bubble Sort: ");

    return 0;
}