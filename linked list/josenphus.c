
// Iterative------------------->
 #include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 100

// Define the structure for the circular linked list node
typedef struct Node {
    char info[MAXLEN];  // Name of the soldier
    struct Node* next;  // Pointer to the next node
} Node;

// Function to insert a node at the rear of the circular linked list
void insert(Node** list, char* name) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    strcpy(new_node->info, name);
    if (*list == NULL) {
        *list = new_node;
        new_node->next = new_node;  // Circular link to itself
    } else {
        Node* temp = *list;
        while (temp->next != *list) {
            temp = temp->next;
        }
        temp->next = new_node;
        new_node->next = *list;
    }
}

// Function to delete the node after the current position
void delafter(Node** list, char* name) {
    Node* to_delete = (*list)->next;
    strcpy(name, to_delete->info);  // Copy the name of the node to be deleted
    (*list)->next = to_delete->next;
    if (to_delete == *list) {
        *list = (*list)->next;  // Update the list pointer if necessary
    }
    free(to_delete);
}

// Function to free the remaining node
void freenode(Node* list) {
    free(list);
}

// Function to solve the Josephus problem
void josephus(void) {
    char end[MAXLEN] = "end";
    char name[MAXLEN];
    int n, i;
    Node* list = NULL;

    printf("Enter n: ");
    scanf("%d", &n);

    printf("Enter names (type 'end' to finish entering):\n");

    // Form the circular linked list by reading names
    while (1) {
        scanf("%s", name);
        if (strcmp(name, end) == 0) {
            break;
        }
        insert(&list, name);
    }

    printf("The order in which the soldiers are eliminated is:\n");

    // Continue eliminating nodes until one remains
    while (list->next != list) {
        for (i = 1; i < n; i++) {
            list = list->next;  // Move to the next node
        }
        delafter(&list, name);
        printf("%s\n", name);  // Print the eliminated name
    }

    // Print the last remaining soldier
    printf("The soldier who escapes is: %s\n", list->info);
    freenode(list);
}

int main() {
    josephus();
    return 0;
}
