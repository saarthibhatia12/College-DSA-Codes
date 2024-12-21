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
Node* insert(Node* list, char* name) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    strcpy(new_node->info, name);
    if (list == NULL) {
        new_node->next = new_node;  // Circular link to itself
        return new_node;
    } else {
        Node* temp = list;
        while (temp->next != list) {
            temp = temp->next;
        }
        temp->next = new_node;
        new_node->next = list;
        return list;
    }
}

// Function to delete the node after the current position
Node* delafter(Node* list, char* name) {
    Node* to_delete = list->next;
    strcpy(name, to_delete->info);  // Copy the name of the node to be deleted
    if (to_delete == list) {        // If there is only one node
        free(to_delete);
        return NULL;
    }
    list->next = to_delete->next;
    free(to_delete);
    return list;
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
        list = insert(list, name);
    }

    printf("The order in which the soldiers are eliminated is:\n");

    // Continue eliminating nodes until one remains
    while (list != NULL && list->next != list) {
        for (i = 1; i < n; i++) {
            list = list->next;  // Move to the next node
        }
        list = delafter(list, name);
        printf("%s\n", name);  // Print the eliminated name
    }

    // Print the last remaining soldier
    if (list != NULL) {
        printf("The soldier who escapes is: %s\n", list->info);
        free(list);
    }
}

int main() {
    josephus();
    return 0;
}
