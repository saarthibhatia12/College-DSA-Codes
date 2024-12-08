#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node* next;
};

// Queue structure
struct Queue {
    struct Node* front;
    struct Node* rear;
};

// Function to create a new node
struct Node* newNode(int data) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

// Function to create a new queue
struct Queue* createQueue() {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}

// Function to add an element to the queue
void enqueue(struct Queue* q, int data) {
    struct Node* temp = newNode(data);
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        q->rear->next = q->front; // Circular link
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
    q->rear->next = q->front; // Circular link
}

// Function to remove an element from the queue
int dequeue(struct Queue* q) {
    if (q->front == NULL) {
        printf("Queue is empty\n");
        return -1;
    }
    int data;
    if (q->front == q->rear) {
        data = q->front->data;
        free(q->front);
        q->front = q->rear = NULL;
    } else {
        struct Node* temp = q->front;
        data = temp->data;
        q->front = q->front->next;
        q->rear->next = q->front; // Circular link
        free(temp);
    }
    return data;
}

// Function to display the queue
void displayQueue(struct Queue* q) {
    if (q->front == NULL) {
        printf("Queue is empty\n");
        return;
    }
    struct Node* temp = q->front;
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != q->front);
    printf("\n");
}

// Main function to test the queue
int main() {
    struct Queue* q = createQueue();
    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);
    enqueue(q, 40);

    printf("Queue: ");
    displayQueue(q);

    printf("Dequeued: %d\n", dequeue(q));
    printf("Queue after dequeue: ");
    displayQueue(q);


    return 0;
}
