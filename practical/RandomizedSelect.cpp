// Write a program to find the ith smallest element of an array using Randomized Select.
#include <iostream>
#include <cstdlib> // For rand()

using namespace std;

// Function to swap two elements
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// Partition function with random pivot
int randomizedPartition(int arr[], int low, int high) {
    int randomIndex = low + rand() % (high - low + 1); // Generate random pivot index
    swap(arr[randomIndex], arr[high]);                // Move pivot to the end

    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1; // Return the position of the pivot
}

// Randomized Select function
int randomizedSelect(int arr[], int low, int high, int i) {
    if (low == high) {
        return arr[low]; // Base case: Only one element
    }

    int pivotIndex = randomizedPartition(arr, low, high);
    int k = pivotIndex - low + 1; // Number of elements in the left partition, including pivot

    if (i == k) {
        return arr[pivotIndex]; // Found the ith smallest element
    } else if (i < k) {
        return randomizedSelect(arr, low, pivotIndex - 1, i); // Search in the left partition
    } else {
        return randomizedSelect(arr, pivotIndex + 1, high, i - k); // Search in the right partition
    }
}

int main() {
    int n, i;
    cout << "Enter the number of elements: ";
    cin >> n;

    int arr[n];
    cout << "Enter the elements of the array: ";
    for (int j = 0; j < n; j++) {
        cin >> arr[j];
    }

    cout << "Enter the value of i (1-based index): ";
    cin >> i;

    if (i < 1 || i > n) {
        cout << "Invalid input for i. It should be between 1 and " << n << "." << endl;
        return 1;
    }

    int result = randomizedSelect(arr, 0, n - 1, i);
    cout << "The " << i << "th smallest element is: " << result << endl;

    return 0;
}
