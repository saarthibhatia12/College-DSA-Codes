#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
} Node;

// Function to create a new node
Node* createNode(int data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = newNode->next = NULL;
    return newNode;
}

// Function to insert at the beginning
Node* insertAtBeginning(Node *head, int data) {
    Node *newNode = createNode(data);
    if (head == NULL) {
        newNode->next = newNode->prev = newNode;
        return newNode;
    }

    Node *tail = head->prev;
    newNode->next = head;
    newNode->prev = tail;
    tail->next = newNode;
    head->prev = newNode;
    return newNode;
}

// Function to insert at the end
Node* insertAtEnd(Node *head, int data) {
    if (head == NULL) {
        return insertAtBeginning(head, data);
    }

    Node *newNode = createNode(data);
    Node *tail = head->prev;
    newNode->next = head;
    newNode->prev = tail;
    tail->next = newNode;
    head->prev = newNode;
    return head;
}

// Function to insert after a specific position
Node* insertAfterPosition(Node *head, int position, int data) {
    if (head == NULL) {
        printf("List is empty. Insert at beginning instead.\n");
        return head;
    }

    Node *current = head;
    for (int i = 0; i < position; i++) {
        current = current->next;
        if (current == head) {
            printf("Position out of range.\n");
            return head;
        }
    }

    Node *newNode = createNode(data);
    newNode->next = current->next;
    newNode->prev = current;
    current->next->prev = newNode;
    current->next = newNode;
    return head;
}

// Function to delete the first node
Node* deleteFromBeginning(Node *head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return NULL;
    }

    Node *tail = head->prev;
    Node *temp = head;

    if (head == head->next) {
        free(head);
        return NULL;
    }

    tail->next = head->next;
    head->next->prev = tail;
    head = head->next;
    free(temp);
    return head;
}

// Function to delete the last node
Node* deleteFromEnd(Node *head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return NULL;
    }

    Node *tail = head->prev;
    if (head == tail) {
        free(head);
        return NULL;
    }

    tail->prev->next = head;
    head->prev = tail->prev;
    free(tail);
    return head;
}

// Function to delete a node at a specific position
Node* deleteAtPosition(Node *head, int position) {
    if (head == NULL) {
        printf("List is empty.\n");
        return NULL;
    }

    Node *current = head;
    for (int i = 0; i < position; i++) {
        current = current->next;
        if (current == head) {
            printf("Position out of range.\n");
            return head;
        }
    }

    if (current == head) {
        return deleteFromBeginning(head);
    }

    current->prev->next = current->next;
    current->next->prev = current->prev;
    free(current);
    return head;
}

// Function to display the list
void displayList(Node *head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    Node *temp = head;
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("\n");
}

// Main function to demonstrate the operations
int main() {
    Node *head = NULL;

    head = insertAtBeginning(head, 10);
    head = insertAtEnd(head, 20);
    head = insertAtEnd(head, 30);
    head = insertAfterPosition(head, 1, 25);

    printf("List after insertions: ");
    displayList(head);

    head = deleteFromBeginning(head);
    printf("List after deleting from beginning: ");
    displayList(head);

    head = deleteFromEnd(head);
    printf("List after deleting from end: ");
    displayList(head);

    head = deleteAtPosition(head, 1);
    printf("List after deleting at position 1: ");
    displayList(head);

    return 0;
}
