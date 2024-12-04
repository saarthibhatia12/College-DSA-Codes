#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node
{
    int data;
    struct Node *next;
} Node;

Node *getNode(int ele)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = ele;
    newNode->next = NULL;
    return newNode;
}

Node *insert_end(Node *head, int ele)
{
    if (head == NULL)
    {
        return getNode(ele);
    }
    if (head->next == NULL)
    {
        Node *newNode = getNode(ele);
        head->next = newNode;
        return head;
    }
    else
    {
        Node *temp = head;
        Node *newNode = getNode(ele);
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
        return head;
    }
}

Node *converter(Node *head, char *a)
{
    int n = strlen(a);
    for (int i = 0; i < n; i++)
    {
        head = insert_end(head, a[i] - '0');
    }
    return head;
}

Node *reverse(Node *head)
{
    if (head->next == NULL)
        return head;
    Node *prev = NULL;
    Node *temp = head;
    Node *front = temp->next;
    while (temp != NULL)
    {
        front = temp->next;
        temp->next = prev;
        prev = temp;
        temp = front;
    }
    return prev;
}

Node *add(Node *head1, Node *head2)
{
    head1 = reverse(head1);
    head2 = reverse(head2);
    Node *t1 = head1;
    Node *t2 = head2;

    Node *dummy = getNode(-1);
    int carry = 0;
    Node *curr = dummy;
    while (t1 != NULL || t2 != NULL)
    {
        int sum = carry;
        if (t1)
            sum += t1->data;
        if (t2)
            sum += t2->data;
        dummy = insert_end(dummy, sum % 10);
        carry = sum / 10;
        if (t1)
            t1 = t1->next;
        if (t2)
            t2 = t2->next;
    }
    if (carry)
    {
        dummy = insert_end(dummy, carry);
    }

    dummy = reverse(dummy->next);
    disp(dummy);
}

void disp(Node *head)
{
    if (head == NULL)
        printf("\nList empty...");
    Node *temp = head;
    while (temp != NULL)
    {
        printf("%d", temp->data);
        temp = temp->next;
    }
}

int main()
{
    char n1[20], n2[20];
    Node *head1 = NULL;
    Node *head2 = NULL;
    Node *head = NULL;
    printf("\nEnter number 1 : ");
    scanf("%s", n1);
    printf("\nEnter number 2 : ");
    scanf("%s", n2);
    head1 = converter(head1, n1);
    head2 = converter(head2, n2);
    head = add(head1, head2);
}
