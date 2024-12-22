#include <stdio.h>
#include <stdlib.h>

// Define the structure of a node in the threaded binary tree
struct Node {
    int info;
    struct Node *left, *right;
    int lthread; // Indicates if the left pointer is a thread
};

// Function to perform reverse inorder traversal on a left-threaded binary tree
void reverseInorderTraversal(struct Node *root) {
    struct Node *currentNode, *previousNode;
    currentNode = root;
    do {
        previousNode = NULL;
        while (currentNode != NULL) {
            previousNode = currentNode;
            currentNode = currentNode->right;
        }
        if (previousNode != NULL) {
            printf("%d ", previousNode->info);
            currentNode = previousNode->left;
            while (previousNode->lthread && currentNode != NULL) {
                printf("%d ", currentNode->info);
                previousNode = currentNode;
                currentNode = currentNode->left;
            }
        }
    } while (previousNode != NULL);
}

// Function to create a new node with left threading
struct Node *createNode(int value) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->info = value;
    newNode->left = newNode->right = NULL;
    newNode->lthread = 1; // True indicates the left pointer is a thread
    return newNode;
}

// Function to set the left child of a node
void setLeftChild(struct Node *parentNode, int value) {
    if (parentNode == NULL || !parentNode->lthread) {
        printf("Cannot insert left child!\n");
    } else {
        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->info = value;
        struct Node *temp = parentNode->left; // Save the reverse inorder predecessor of parentNode
        parentNode->left = newNode;
        parentNode->lthread = 0; // False indicates the left pointer is not a thread
        newNode->right = NULL;
        newNode->left = temp; // Reverse inorder predecessor is the previous predecessor of parentNode
        newNode->lthread = 1; // True indicates the left pointer is a thread
    }
}

// Function to set the right child of a node
void setRightChild(struct Node *parentNode, int value) {
    if (parentNode == NULL || parentNode->right != NULL) {
        printf("Cannot insert right child!\n");
    } else {
        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->info = value;
        parentNode->right = newNode;
        newNode->right = NULL;
        newNode->left = parentNode; // Reverse inorder predecessor
        newNode->lthread = 1; // True indicates the left pointer is a thread
    }
}

int main() {
    // Example usage of the functions
    struct Node *root = createNode(10);
    setRightChild(root, 15);
    setLeftChild(root, 5);
    setRightChild(root->left, 7);
    setLeftChild(root->left, 2);

    printf("Reverse Inorder Traversal of Left-Threaded Binary Tree:\n");
    reverseInorderTraversal(root);

    return 0;
}

