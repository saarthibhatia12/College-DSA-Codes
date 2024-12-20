#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct node
{
    char data;
    struct node *left;
    struct node *right;
} Node;

typedef struct stack
{
    int top;
    Node *data[10];
} STACK;

void push(STACK *s, Node *item)
{
    s->data[++(s->top)] = item;
}

Node *pop(STACK *s)
{
    return s->data[(s->top)--];
}

int preced(char symbol)
{
    switch (symbol)
    {
    case '$':
        return 5;
    case '*':
    case '/':
        return 3;
    case '+':
    case '-':
        return 1;
    default:
        return 0;
    }
}

Node *create_node(char item)
{
    Node *temp;
    temp = (Node *)malloc(sizeof(Node));
    temp->data = item;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

void preorder(Node *root)
{
    if (root != NULL)
    {
        printf("%c", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void inorder(Node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%c", root->data);
        inorder(root->right);
    }
}

void postorder(Node *root)
{
    if (root != NULL)
    {
        postorder(root->left);
        postorder(root->right);
        printf("%c", root->data);
    }
}

Node *create_expr_tree(Node *root, char infix[10])
{
    STACK *TS = (STACK *)malloc(sizeof(STACK));
    STACK *OS = (STACK *)malloc(sizeof(STACK));
    TS->top = -1;
    OS->top = -1;

    int i;
    char symbol;
    Node *temp, *t;

    for (i = 0; infix[i] != '\0'; i++)
    {
        symbol = infix[i];
        temp = create_node(symbol);

        if (isalnum(symbol))
        {
            push(TS, temp);
        }
        else
        {
            if (OS->top == -1)
            {
                push(OS, temp);
            }
            else
            {
                while (OS->top != -1 && preced(OS->data[OS->top]->data) >= preced(symbol))
                {
                    t = pop(OS);
                    t->right = pop(TS);
                    t->left = pop(TS);
                    push(TS, t);
                }
                push(OS, temp);
            }
        }
    }

    while (OS->top != -1)
    {
        t = pop(OS);
        t->right = pop(TS);
        t->left = pop(TS);
        push(TS, t);
    }

    free(OS);
    root = pop(TS);
    free(TS);

    return root;
}

int main()
{
    char infix[10];
    Node *root = NULL;

    printf("\n Read the infix expression :");
    scanf("%s", infix);

    root = create_expr_tree(root, infix);

    printf("\n The preorder traversal is\n");
    preorder(root);

    printf("\n The inorder traversal is\n");
    inorder(root);

    printf("\n The postorder traversal is\n");
    postorder(root);

    return 0;
}

