#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

typedef struct {
    int top;
    int items[MAX];
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int isFull(Stack *s) {
    return s->top == MAX - 1;
}

void push(Stack *s, int value) {
    if (isFull(s)) {
        printf("Stack overflow\n");
        exit(1);
    }
    s->items[++(s->top)] = value;
}

int pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack underflow\n");
        exit(1);
    }
    return s->items[(s->top)--];
}

int evaluatePrefix(char *exp) {
    Stack s;
    initStack(&s);
    int length = strlen(exp);

    for (int i = length - 1; i >= 0; i--) {
        if (isdigit(exp[i])) {
            push(&s, exp[i] - '0');
        } else {
            int op1 = pop(&s);
            int op2 = pop(&s);
            switch (exp[i]) {
                case '+': push(&s, op1 + op2); break;
                case '-': push(&s, op1 - op2); break;
                case '*': push(&s, op1 * op2); break;
                case '/': push(&s, op1 / op2); break;
                default: printf("Invalid operator: %c\n", exp[i]); exit(1);
            }
        }
    }
    return pop(&s);
}

int main() {
    char exp[MAX];
    printf("Enter a prefix expression: ");
    scanf("%s", exp);
    int result = evaluatePrefix(exp);
    printf("The result of the prefix expression is: %d\n", result);
    return 0;
}
