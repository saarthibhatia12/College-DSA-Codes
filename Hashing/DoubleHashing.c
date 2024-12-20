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
    while (hashTable[(index + i * step) % TABLE_SIZE] != -1 &&
           hashTable[(index + i * step) % TABLE_SIZE] != -2 && // Skip deleted slots
           i < TABLE_SIZE) {
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

// Function to delete a key from the hash table
void deleteKey(int key) {
    int index = search(key);
    if (index != -1) {
        hashTable[index] = -2; // Mark the slot as deleted
        printf("Key %d deleted successfully.\n", key);
    } else {
        printf("Key %d not found!\n", key);
    }
}

// Function to display the hash table
void display() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hashTable[i] == -1) {
            printf("Index %d: ~\n", i);
        } else if (hashTable[i] == -2) {
            printf("Index %d: (Deleted)\n", i);
        } else {
            printf("Index %d: %d\n", i, hashTable[i]);
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
                printf("Key %d found at index %d\n", key, result);
            } else {
                printf("Key %d not found!\n", key);
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
