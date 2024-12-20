#include <stdio.h> 
#include <stdlib.h> 

// Function to heapify an array to create a max-heap
void heapify(int a[10], int n)
{
    int i, k, v, j, flag = 0; // Variables:
                              // i = current parent index
                              // k = parent being adjusted
                              // v = value of the parent node
                              // j = child index
                              // flag = stop condition
    for (i = n / 2; i >= 1; i--) // Start from the last parent node (n/2) and go up to the root (1).
    {
        k = i;                // Start adjusting the parent at index `i`.
        v = a[k];             // Save the parent value.
        while (!flag && 2 * k <= n) // Keep adjusting while the node has children.
        {
            j = 2 * k;        // Left child index.
            if (j < n)        // Check if the right child exists.
            {
                if (a[j] < a[j + 1]) // If right child is larger, use it.
                    j = j + 1;
            }
            if (v >= a[j])    // If the parent is larger than or equal to the larger child, stop.
                flag = 1;
            else              // Otherwise, swap parent with the larger child.
            {
                a[k] = a[j];
                k = j;        // Move down to the child position.
            }
        }
        a[k] = v;            // Place the original parent value in the correct position.
        flag = 0;            // Reset flag for the next iteration.
    }
}

// Main function
int main() 
{ 
    int n, i, a[10], ch; 

    // Infinite loop for menu-driven program
    for (;;) 
    { 
        // Display menu options
        printf("\n 1. Create Heap"); 
        printf("\n 2. Extractmax"); 
        printf("\n 3. Exit"); 
        printf("\n Read Choice :"); 

        // Read user's choice
        scanf("%d", &ch); 

        switch (ch) 
        { 
            case 1: 
                // Read the number of elements in the heap
                printf("\n Read no of elements :"); 
                scanf("%d", &n); 

                // Read the elements into the array
                printf("\n Read Elements\n"); 
                for (i = 1; i <= n; i++) 
                    scanf("%d", &a[i]); 

                // Call heapify to create a max-heap
                heapify(a, n); 

                // Display the heap
                printf("\n Elements after heap\n"); 
                for (i = 1; i <= n; i++) 
                    printf("%d\t", a[i]); 
                break; 

            case 2: 
                // If there are elements in the heap, extract the maximum
                if (n >= 1) 
                { 
                    printf("\n Element deleted is %d\n", a[1]); // Maximum element is at root
                    a[1] = a[n]; // Move the last element to the root
                    n = n - 1; // Reduce the size of the heap

                    // Re-heapify the array to maintain the heap property
                    heapify(a, n); 

                    // Display the updated heap if it isn't empty
                    if (n != 0) 
                    { 
                        printf("\n Elements after reconstructing heap\n"); 
                        for (i = 1; i <= n; i++) 
                            printf("%d\t", a[i]); 
                    } 
                } 
                else 
                {
                    // If heap is empty, inform the user
                    printf("\n No element to delete"); 
                }
                break; 

            default: 
                // Exit the program
                exit(0); 
        } 
    } 

    return 0; 
}
