#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
} Node;

// Function to create a new node
Node* create_node(int data) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

// Insertion at the empty list
Node* insert_empty(Node *head, int data) {
    if (head != NULL) return head;
    return create_node(data);
}

// Insertion at the beginning
Node* insert_beginning(Node *head, int data) {
    Node *new_node = create_node(data);
    if (head == NULL) return new_node;
    new_node->next = head;
    head->prev = new_node;
    head=new_node;
    return head;
}

// Insertion at the end
Node* insert_end(Node *head, int data) {
    Node *new_node = create_node(data);
    if (head == NULL) return new_node;
    Node *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_node;
    new_node->prev = temp;
    return head;
}

// Insertion at a given position
Node* insert_at_position(Node *head, int data, int pos) {
    if (head == NULL || pos <= 1) return insert_beginning(head, data);
    Node *new_node = create_node(data);
    Node *temp = head;
    for (int i = 1; i < pos - 1 && temp->next != NULL; i++) {
        temp = temp->next;
    }
    new_node->next = temp->next;
    new_node->prev = temp;
    if (temp->next != NULL) temp->next->prev = new_node;
    temp->next = new_node;
    return head;
}

// Delete the first node
Node* delete_first(Node *head) {
    if (head == NULL) return NULL;
    Node *temp = head;
    head = head->next;
    if (head != NULL) head->prev = NULL;
    free(temp);
    return head;
}

// Delete the last node
Node* delete_last(Node *head) {
    if (head == NULL) return NULL;
    Node *temp = head;
    if (temp->next == NULL) { // Only one node in list
        free(temp);
        return NULL;
    }
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->prev->next = NULL;
    free(temp);
    return head;
}

// Delete a node at a given position
Node* delete_at_position(Node *head, int pos) {
    if (head == NULL) return NULL;
    if (pos == 1) return delete_first(head);
    Node *temp = head;
    for (int i = 1; i < pos && temp != NULL; i++) {
        temp = temp->next;
    }
    if (temp == NULL) return head; // Position out of range
    if (temp->next != NULL) temp->next->prev = temp->prev;
    if (temp->prev != NULL) temp->prev->next = temp->next;
    free(temp);
    return head;
}

// Search for a node
int search(Node *head, int key) {
    Node *temp = head;
    while (temp != NULL) {
        if (temp->data == key) return 1;
        temp = temp->next;
    }
    return 0;
}

// Display the list
void display(Node *head) {
    Node *temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    Node *head = NULL;
    head = insert_empty(head, 10);
    head = insert_end(head, 20);
    head = insert_end(head, 30);
    head = insert_beginning(head, 5);
    head = insert_at_position(head, 25, 3);
    
    printf("List after insertions: ");
    display(head);

    head = delete_first(head);
    printf("List after deleting first node: ");
    display(head);

    head = delete_last(head);
    printf("List after deleting last node: ");
    display(head);

    head = delete_at_position(head, 2);
    printf("List after deleting node at position 2: ");
    display(head);

    int key = 20;
    printf("Search for %d: %s\n", key, search(head, key) ? "Found" : "Not Found");

    return 0;
}
