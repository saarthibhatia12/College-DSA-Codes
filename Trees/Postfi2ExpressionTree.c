#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Define a structure for tree nodes
typedef struct Node {
    char data;
    struct Node* left;
    struct Node* right;
} Node;

// Function to create a new tree node
Node* createNode(char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Stack structure to store tree nodes
typedef struct Stack {
    Node* data[100];
    int top;
} Stack;

// Initialize the stack
void initStack(Stack* stack) {
    stack->top = -1;
}

// Push a node onto the stack
void push(Stack* stack, Node* node) {
    stack->data[++stack->top] = node;
}

// Pop a node from the stack
Node* pop(Stack* stack) {
    return stack->data[stack->top--];
}

// Function to convert postfix expression to expression tree
Node* createExpressionTree(char* postfix) {
    Stack stack;
    initStack(&stack);

    for (int i = 0; postfix[i] != '\0'; i++) {
        char symb = postfix[i];

        if (isalnum(symb)) {  // Operand
            Node* newNode = createNode(symb);
            push(&stack, newNode);
        } else {  // Operator
            Node* right = pop(&stack);
            Node* left = pop(&stack);
            Node* root = createNode(symb);
            root->left = left;
            root->right = right;
            push(&stack, root);
        }
    }
    return pop(&stack);
}

// Function to print the tree (in-order traversal)
void inorderTraversal(Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%c ", root->data);
        inorderTraversal(root->right);
    }
}

// Main function
int main() {
    char postfix[] = "ab+c*";  // Example postfix expression
    Node* root = createExpressionTree(postfix);

    printf("In-order Traversal of the Expression Tree:\n");
    inorderTraversal(root);
    printf("\n");

    return 0;
}
