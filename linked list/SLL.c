#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node *next;
}Node;

Node *create_node(int data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

Node *convertarr2ll(int arr[], int size) {
    if (size == 0) return NULL;
    Node *head = create_node(arr[0]);
    Node *mover = head;
    for (int i = 1; i < size; ++i) {
        Node *temp = create_node(arr[i]);
        mover->next = temp;
        mover = temp;
    }
    return head;
}

int lengthofll(Node *head) {
    Node *temp = head;
    int cnt = 0;
    while (temp != NULL) {
        temp = temp->next;
        cnt++;
    }
    return cnt;
}

void print(Node *head) {
    Node *temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

Node *removehead(Node *head) {
    if (head == NULL) return head;
    Node *temp = head;
    head = head->next;
    free(temp);
    return head;
}

Node *removetail(Node *head) {
    if (head == NULL || head->next == NULL) return NULL;
    Node *temp = head;
    while (temp->next->next != NULL) {
        temp = temp->next;
    }
    free(temp->next);
    temp->next = NULL;
    return head;
}

Node *removeK(Node *head, int k) {
    if (head == NULL) return head;
    if (k == 1) {
        Node *temp = head;
        head = head->next;
        free(temp);
        return head;
    }
    int cnt = 0;
    Node *temp = head;
    Node *prev = NULL;
    while (temp != NULL) {
        cnt++;
        if (cnt == k) {
            prev->next = prev->next->next;
            free(temp);
            break;
        }
        prev = temp;
        temp = temp->next;
    }
    return head;
}

Node *remove_val(Node *head, int val) {
    if (head == NULL) return head;
    if (head->data == val) {
        Node *temp = head;
        head = head->next;
        free(temp);
        return head;
    }
    Node *temp = head;
    Node *prev = NULL;
    while (temp != NULL) {
        if (temp->data == val) {
            prev->next = prev->next->next;
            free(temp);
            break;
        }
        prev = temp;
        temp = temp->next;
    }
    return head;
}

Node *insert_at_beginning(Node *head, int k) {
    Node *temp = create_node(k);
    temp->next = head;
    head = temp;
    return head;
}
Node *insert_at_end(Node *head, int data) {
    Node *new_node = create_node(data);
    if (head == NULL) {
        return new_node;
    }
    Node *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_node;
    return head;
}


Node *insertatposition(Node *head, int el, int k) {
    if (head == NULL) {
        if (k == 1) {
            return create_node(el);
        } else {
            return head;
        }
    }
    if (k == 1) {
        return create_node(el);
    }
    int cnt = 0;
    Node *temp = head;
    while (temp != NULL) {
        cnt++;
        if (cnt == k - 1) {
            Node *x = create_node(el);
            x->next = temp->next;
            temp->next = x;
            break;
        }
        temp = temp->next;
    }
    return head;
}

Node *insertBeforval(Node *head, int el, int val) {
    if (head == NULL) {
        return NULL;
    }
    if (head->data == val) {
        return create_node(el);
    }
    Node *temp = head;
    while (temp->next != NULL) {
        if (temp->next->data == val) {
            Node *x = create_node(el);
            x->next = temp->next;
            temp->next = x;
            break;
        }
        temp = temp->next;
    }
    return head;
}
int main() {
    int arr[] = {1, 2, 3, 4};
    Node *head = convertarr2ll(arr, 4);
    print(head);
    head = insert_at_end(head, 5);
    print(head);
    return 0;
}
