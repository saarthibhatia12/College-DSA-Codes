#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

// Structure for a node in the linked list
typedef struct Node {
    int key;
    struct Node* next;
} Node;

// Hash table with separate chaining
Node* hashTable[TABLE_SIZE];

// Function to calculate the hash index
int hashFunction(int key) {
    return key % TABLE_SIZE;
}

// Function to create a new node
Node* createNode(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a key into the hash table
void insert(int key) {
    int index = hashFunction(key);
    Node* newNode = createNode(key);

    // Insert the new node at the beginning of the chain
    if (hashTable[index] == NULL) {
        hashTable[index] = newNode;
    } else {
        newNode->next = hashTable[index];
        hashTable[index] = newNode;
    }
}

// Function to search for a key in the hash table
int search(int key) {
    int index = hashFunction(key);
    Node* temp = hashTable[index];

    while (temp != NULL) {
        if (temp->key == key) {
            return index;
        }
        temp = temp->next;
    }
    return -1; // Key not found
}

// Function to delete a key from the hash table
void deleteKey(int key) {
    int index = hashFunction(key);
    Node* temp = hashTable[index];
    Node* prev = NULL;

    while (temp != NULL) {
        if (temp->key == key) {
            if (prev == NULL) { // Key is at the head of the list
                hashTable[index] = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
            printf("Key %d deleted successfully.\n", key);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Key %d not found!\n", key);
}

// Function to display the hash table
void display() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Index %d: ", i);
        Node* temp = hashTable[i];
        if (temp == NULL) {
            printf("~");
        } else {
            while (temp != NULL) {
                printf("%d -> ", temp->key);
                temp = temp->next;
            }
            printf("NULL");
        }
        printf("\n");
    }
}

int main() {
    // Initialize the hash table to NULL
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }

    int choice, key;
    while (1) {
        printf("\nOpen Hashing Menu:\n");
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
