#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int row, col, data;
    struct node *next;
    struct node *prev;
} Node; // Changed typedef to create an alias 'Node'

Node *insertend(Node *start, int row, int col, int item)
{
    Node *temp, *cur;
    temp = (Node *)malloc(sizeof(Node));
    temp->row = row;
    temp->col = col;
    temp->data = item;
    temp->next = NULL;
    temp->prev = NULL;
    if (start == NULL)
        return temp;
    cur = start;
    while (cur->next != NULL)
        cur = cur->next;
    cur->next = temp;
    temp->prev = cur;
    return start;
}

void display(Node *start)
{
    Node *temp;
    if (start == NULL)
        printf("\nList is empty\n");
    else
    {
        printf("\nROW\tCOL\tDATA\n");
        temp = start;
        while (temp != NULL)
        {
            printf("%d\t%d\t%d\n", temp->row, temp->col, temp->data);
            temp = temp->next;
        }
    }
}

void displaymatrix(Node *start, int m, int n)
{
    Node *temp;
    int i, j;
    temp = start;
    printf("\nThe Sparse Matrix is:\n");
    for (i = 1; i <= m; i++)
    {
        for (j = 1; j <= n; j++)
        {
            if (temp != NULL && temp->row == i && temp->col == j)
            {
                printf("%d\t", temp->data);
                temp = temp->next;
            }
            else
                printf("0\t");
        }
        printf("\n");
    }
}

int main()
{
    Node *start = NULL;
    int i, j, m, n, item;
    printf("\nEnter the order of the matrix (rows and columns):\n");
    scanf("%d%d", &m, &n);
    printf("\nEnter the matrix elements row by row:\n");
    for (i = 1; i <= m; i++)
    {
        for (j = 1; j <= n; j++)
        {
            scanf("%d", &item);
            if (item != 0)
                start = insertend(start, i, j, item);
        }
    }
    display(start);
    displaymatrix(start, m, n);
    return 0;
}
