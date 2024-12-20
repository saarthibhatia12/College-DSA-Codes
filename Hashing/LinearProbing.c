#include <stdio.h>
#include <stdlib.h>
#define TABLE_SIZE 10  // Size of the hash table

int hashTable[TABLE_SIZE];  // The hash table
int size = 0;  // Current number of elements in the table

// Function to initialize the hash table
void initializeTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = -1;  // -1 indicates an empty slot
    }
}

// Function to calculate hash value
int hashFunction(int key) {
    return key % TABLE_SIZE;
}

// Function to insert a key into the hash table
void insert(int key) {
    if (size == TABLE_SIZE) {
        printf("Hash table is full! Unable to insert %d.\n", key);
        return;
    }

    int index = hashFunction(key);
    while (hashTable[index] != -1) {
        index = (index + 1) % TABLE_SIZE;  // Linear probing
    }

    hashTable[index] = key;
    size++;
    printf("Key %d inserted at index %d.\n", key, index);
}

// Function to search for a key in the hash table
int search(int key) {
    int index = hashFunction(key);
    int start = index;  // Save the starting index

    while (hashTable[index] != -1) {
        if (hashTable[index] == key) {
            return index;  // Key found
        }
        index = (index + 1) % TABLE_SIZE;

        if (index == start) {
            break;  // We've cycled back to the start
        }
    }

    return -1;  // Key not found
}

// Function to delete a key from the hash table
void deleteKey(int key) {
    int index = search(key);
    if (index == -1) {
        printf("Key %d not found in the hash table.\n", key);
        return;
    }

    hashTable[index] = -1;  // Mark the slot as empty
    size--;
    printf("Key %d deleted from index %d.\n", key, index);
}

// Function to display the hash table
void display() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hashTable[i] == -1) {
            printf("Index %d: ~\n", i);
        } else {
            printf("Index %d: %d\n", i, hashTable[i]);
        }
    }
}

// Main function
int main() {
    int choice, key;

    initializeTable();

    while (1) {
        printf("\nHash Table Menu:\n");
        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Delete\n");
        printf("4. Display\n");
        printf("5. Exit\n");
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
                printf("Key %d found at index %d.\n", key, result);
            } else {
                printf("Key %d not found in the hash table.\n", key);
            }
            break;
        case 3:
            printf("Enter key to delete: ");
            scanf("%d", &key);
            deleteKey(key);
            break;
        case 4:
            display();
            break;
        case 5:
            exit(0);
        default:
            printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
