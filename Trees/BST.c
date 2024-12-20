#include <stdio.h> 
#include <stdlib.h> 

// Define the structure for a tree node
struct node 
{ 
    int data; 
    struct node *left; 
    struct node *right; 
}; 

typedef struct node Node; // Typedef for simpler usage of struct node as Node

// Function to create a new node
Node* create_node(int item) 
{ 
    Node* temp; 
    temp = (Node*)malloc(sizeof(Node)); // Allocate memory for the new node
    temp->data = item; // Assign the data
    temp->left = NULL; // Initialize left child as NULL
    temp->right = NULL; // Initialize right child as NULL
    return temp; 
} 

// Function to insert a new element into the BST
Node* Insertbst(Node* root, int item) 
{ 
    Node* temp; 
    temp = create_node(item); 
    if (root == NULL) 
        return temp; // If tree is empty, the new node becomes the root
    else 
    { 
        if (item < root->data) // If item is smaller, go to the left subtree
            root->left = Insertbst(root->left, item); 
        else // If item is larger or equal, go to the right subtree
            root->right = Insertbst(root->right, item); 
    } 
    return root; 
} 

// Function for preorder traversal (Root -> Left -> Right)
void preorder(Node* root) 
{ 
    if (root != NULL) 
    { 
        printf("%d\t", root->data); 
        preorder(root->left); 
        preorder(root->right); 
    } 
} 

// Function for inorder traversal (Left -> Root -> Right)
void inorder(Node* root) 
{ 
    if (root != NULL) 
    { 
        inorder(root->left); 
        printf("%d\t", root->data); 
        inorder(root->right); 
    } 
} 

// Function for postorder traversal (Left -> Right -> Root)
void postorder(Node* root) 
{ 
    if (root != NULL) 
    { 
        postorder(root->left); 
        postorder(root->right); 
        printf("%d\t", root->data); 
    } 
} 

// Function to find the inorder successor (smallest node in right subtree)
Node* inordersuccessor(Node* root) 
{ 
    Node* cur = root; 
    while (cur->left != NULL) 
        cur = cur->left; // Traverse to the leftmost node
    return cur; 
} 

// Function to delete a node from the BST
Node* deletenode(Node* root, int key) 
{ 
    Node* temp; 
    if (root == NULL) 
        return NULL; // If tree is empty, return NULL
    if (key < root->data) // If key is smaller, go to the left subtree
        root->left = deletenode(root->left, key); 
    else if (key > root->data) // If key is larger, go to the right subtree
        root->right = deletenode(root->right, key); 
    else // Node to be deleted is found
    { 
        // Node with only one child or no child
        if (root->left == NULL) 
        { 
            temp = root->right; 
            free(root); 
            return temp; 
        } 
        if (root->right == NULL) 
        { 
            temp = root->left; 
            free(root); 
            return temp; 
        } 
        // Node with two children: Get the inorder successor
        temp = inordersuccessor(root->right); 
        root->data = temp->data; // Copy the inorder successor's data
        root->right = deletenode(root->right, temp->data); // Delete the inorder successor
    } 
    return root; 
} 

int main() 
{ 
    Node* root = NULL; // Initialize the root node as NULL
    int ch, item, key; 
    for (;;) 
    { 
        // Menu for user interaction
        printf("\n 1. Insert"); 
        printf("\n 2. Preorder"); 
        printf("\n 3. Inorder"); 
        printf("\n 4. Postorder"); 
        printf("\n 5. Delete"); 
        printf("\n 6. Exit"); 
        printf("\n Read your choice:"); 
        scanf("%d", &ch); 
        switch (ch) 
        { 
            case 1:
                printf("\n Read element to be inserted: "); 
                scanf("%d", &item); 
                root = Insertbst(root, item); // Insert the element into the BST
                break; 
            case 2:
                printf("\n The Preorder traversal is:\n"); 
                preorder(root); // Display preorder traversal
                break; 
            case 3:
                printf("\n The Inorder traversal is:\n"); 
                inorder(root); // Display inorder traversal
                break; 
            case 4:
                printf("\n The Postorder traversal is:\n"); 
                postorder(root); // Display postorder traversal
                break; 
            case 5:
                printf("\n Read node to be deleted: "); 
                scanf("%d", &key); 
                root = deletenode(root, key); // Delete the node with the specified key
                break; 
            default:
                exit(0); // Exit the program
        } 
    } 
    return 0; 
}
