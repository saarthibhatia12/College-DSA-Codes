#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Function to create a new node
Node* create_node(int data) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = new_node; // For circular linked list
    return new_node;
}

// Insertion at the empty list
Node* insert_empty(Node *head, int data) {
    if (head != NULL) return head;
    head = create_node(data);
    head->next = head; // Point to itself
    return head;
}

// Insertion at the beginning
Node* insert_beginning(Node *head, int data) {
    if (head == NULL) return insert_empty(head, data);
    Node *new_node = create_node(data);
    new_node->next = head->next;
    head->next = new_node;
    int temp = head->data;
    head->data = new_node->data;
    new_node->data = temp;
    return head;
}

// Insertion at the end
Node* insert_end(Node *head, int data) {
    if (head == NULL) return insert_empty(head, data); // Insert into an empty list

    Node *new_node = create_node(data);
    Node *temp = head;

    // Traverse to the last node
    while (temp->next != head) {
        temp = temp->next;
    }

    // Insert the new node at the end
    temp->next = new_node;
    new_node->next = head;

    return head; // Return the head, unchanged
}

// Insertion at a given position
Node* insert_at_position(Node *head, int data, int pos) {
    if (head == NULL) return insert_empty(head, data);
    Node *new_node = create_node(data);
    Node *temp = head;
    for (int i = 1; i < pos - 1 && temp->next != head; i++) {
        temp = temp->next;
    }
    new_node->next = temp->next;
    temp->next = new_node;
    return head;
}

// Delete the first node
Node* delete_first(Node *head) {
    if (head == NULL || head->next == head) {
        free(head);
        return NULL;
    }
    Node *temp = head->next;
    head->data = temp->data;
    head->next = temp->next;
    free(temp);
    return head;
}

// Delete the last node
Node* delete_last(Node *head) {
    if (head == NULL || head->next == head) {
        free(head);
        return NULL;
    }
    Node *temp = head;
    while (temp->next->next != head) {
        temp = temp->next;
    }
    Node *last = temp->next;
    temp->next = head;
    free(last);
    return head;
}

// Delete the node at a given position
Node* delete_at_position(Node *head, int pos) {
    if (head == NULL) return NULL;
    if (pos == 1) return delete_first(head);
    Node *temp = head;
    for (int i = 1; i < pos - 1 && temp->next != head; i++) {
        temp = temp->next;
    }
    Node *del_node = temp->next;
    temp->next = del_node->next;
    free(del_node);
    return head;
}

// Search for a node
int search(Node *head, int key) {
    if (head == NULL) return 0;
    Node *temp = head;
    do {
        if (temp->data == key) return 1;
        temp = temp->next;
    } while (temp != head);
    return 0;
}

// Display the list
void display(Node *head) {
    if (head == NULL) return;
    Node *temp = head;
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != head);
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
