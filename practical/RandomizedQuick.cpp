// Write a program to sort the elements of an array using Randomized Quick Sort (the
// program should report the number of comparisons).
#include <iostream>
#include <cstdlib>
using namespace std;

// Function to swap two elements
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// Partition function using the middle element as pivot
int middlePartition(int arr[], int low, int high, int &comparisons) {
    // Select the middle element as pivot
    int randomIndex = low + rand() % (high - low + 1);
    swap(arr[randomIndex], arr[high]); // Move the pivot to the end

    int pivot = arr[high]; // Pivot element
    int i = low - 1;       // Index of the smaller element

    for (int j = low; j < high; j++) {
        comparisons++; // Increment comparison count
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Quick Sort function using middle partitioning
void pseudoRandomQuickSort(int arr[], int low, int high, int &comparisons) {
    if (low < high) {
        int pi = middlePartition(arr, low, high, comparisons);

        // Recursively sort elements before and after partition
        pseudoRandomQuickSort(arr, low, pi - 1, comparisons);
        pseudoRandomQuickSort(arr, pi + 1, high, comparisons);
    }
}

int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    int arr[n];
    cout << "Enter the elements of the array: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int comparisons = 0; // Counter for comparisons

    pseudoRandomQuickSort(arr, 0, n - 1, comparisons);

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    cout << "Number of comparisons: " << comparisons << endl;

    return 0;
}
