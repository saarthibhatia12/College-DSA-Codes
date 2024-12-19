#include <stdio.h>
#include <stdlib.h>

// Function to heapify a subtree rooted at index k
void heapify(int a[], int n, int k) {
    int largest = k; // Initialize largest as root
    int left = 2 * k; // Left child index
    int right = 2 * k + 1; // Right child index

    // Check if left child exists and is greater than root
    if (left <= n && a[left] > a[largest])
        largest = left;

    // Check if right child exists and is greater than largest so far
    if (right <= n && a[right] > a[largest])
        largest = right;

    // If largest is not root
    if (largest != k) {
        int temp = a[k];
        a[k] = a[largest];
        a[largest] = temp;

        // Recursively heapify the affected subtree
        heapify(a, n, largest);
    }
}

// Function to perform heap sort
void heapSort(int a[], int n) {
    // Step 1: Build a max-heap
    for (int i = n / 2; i >= 1; i--)
        heapify(a, n, i);

    // Step 2: Extract elements from the heap
    for (int i = n; i >= 2; i--) {
        // Swap the root (max element) with the last element
        int temp = a[1];
        a[1] = a[i];
        a[i] = temp;

        // Reduce the size of the heap and re-heapify
        heapify(a, i - 1, 1);
    }
}

// Main function
int main() {
    int n, a[10];

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    printf("Enter the elements:\n");
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);

    // Perform heap sort
    heapSort(a, n);

    // Display sorted elements
    printf("Sorted elements:\n");
    for (int i = 1; i <= n; i++)
        printf("%d\t", a[i]);

    return 0;
}
