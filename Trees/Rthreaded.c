#include <stdio.h>
#include <stdlib.h>

// Define the structure of a node in the threaded binary tree
struct Node {
    int info;
    struct Node *left, *right;
    int rthread; // Indicates if the right pointer is a thread
};

// Function to perform inorder traversal on a right-threaded binary tree
void inorderTraversal(struct Node *root) {
    struct Node *currentNode, *previousNode;
    currentNode = root;
    do {
        previousNode = NULL;
        while (currentNode != NULL) {
            previousNode = currentNode;
            currentNode = currentNode->left;
        }
        if (previousNode != NULL) {
            printf("%d ", previousNode->info);
            currentNode = previousNode->right;
            while (previousNode->rthread && currentNode != NULL) {
                printf("%d ", currentNode->info);
                previousNode = currentNode;
                currentNode = currentNode->right;
            }
        }
    } while (previousNode != NULL);
}

// Function to create a new node with right threading
struct Node *createNode(int value) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->info = value;
    newNode->left = newNode->right = NULL;
    newNode->rthread = 1; // True indicates the right pointer is a thread
    return newNode;
}

// Function to set the left child of a node
void setLeftChild(struct Node *parentNode, int value) {
    if (parentNode == NULL || parentNode->left != NULL) {
        printf("Cannot insert left child!\n");
    } else {
        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->info = value;
        parentNode->left = newNode;
        newNode->left = NULL;
        newNode->right = parentNode; // Inorder successor
        newNode->rthread = 1; // True indicates the right pointer is a thread
    }
}

// Function to set the right child of a node
void setRightChild(struct Node *parentNode, int value) {
    if (parentNode == NULL || !parentNode->rthread) {
        printf("Cannot insert right child!\n");
    } else {
        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->info = value;
        struct Node *temp = parentNode->right; // Save the inorder successor of parentNode
        parentNode->right = newNode;
        parentNode->rthread = 0; // False indicates the right pointer is not a thread
        newNode->left = NULL;
        newNode->right = temp; // Inorder successor is the previous successor of parentNode
        newNode->rthread = 1; // True indicates the right pointer is a thread
    }
}

int main() {
    // Example usage of the functions
    struct Node *root = createNode(10);
    setLeftChild(root, 5);
    setRightChild(root, 15);
    setLeftChild(root->left, 2);
    setRightChild(root->left, 7);

    printf("Inorder Traversal of Threaded Binary Tree:\n");
    inorderTraversal(root);

    return 0;
}
