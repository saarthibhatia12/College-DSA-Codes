#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10
#define PRIME 7  // A smaller prime number for the second hash function

int hashTable[TABLE_SIZE];

// Function to calculate the primary hash
int hash1(int key) {
    return key % TABLE_SIZE;
}

// Function to calculate the secondary hash
int hash2(int key) {
    return PRIME - (key % PRIME);
}

// Function to insert a key into the hash table
void insert(int key) {
    int index = hash1(key);
    int step = hash2(key);
    
    int i = 0;
    while (hashTable[(index + i * step) % TABLE_SIZE] != -1 && i < TABLE_SIZE) {
        i++;
    }

    if (i < TABLE_SIZE) {
        hashTable[(index + i * step) % TABLE_SIZE] = key;
    } else {
        printf("Hash table is full! Unable to insert key %d\n", key);
    }
}

// Function to search for a key in the hash table
int search(int key) {
    int index = hash1(key);
    int step = hash2(key);

    int i = 0;
    while (hashTable[(index + i * step) % TABLE_SIZE] != -1 && i < TABLE_SIZE) {
        if (hashTable[(index + i * step) % TABLE_SIZE] == key) {
            return (index + i * step) % TABLE_SIZE;
        }
        i++;
    }

    return -1; // Key not found
}

// Function to display the hash table
void display() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hashTable[i] != -1) {
            printf("Index %d: %d\n", i, hashTable[i]);
        } else {
            printf("Index %d: ~\n", i);
        }
    }
}

int main() {
    // Initialize the hash table with -1 (indicating empty slots)
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = -1;
    }

    int choice, key;
    while (1) {
        printf("\nDouble Hashing Menu:\n");
        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter key to insert: ");
            scanf("%d", &key);
            insert(key);
            break;
        case 2:
            printf("Enter key to search: ");
            scanf("%d", &key);
            int result = search(key);
            if (result != -1) {
                printf("Key %d found at index %d\n", key, result);
            } else {
                printf("Key %d not found!\n", key);
            }
            break;
        case 3:
            display();
            break;
        case 4:
            exit(0);
        default:
            printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
