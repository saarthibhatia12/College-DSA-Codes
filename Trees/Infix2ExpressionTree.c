#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#define MAX 100

typedef struct node{
    char data;
    struct node *right;
    struct node *left;
}NODE;

typedef struct stack{
    int top;
    NODE* item[MAX];
}STACK;

NODE* getNode(char data){
    NODE* temp = (NODE*)malloc(sizeof(NODE));
    temp->right = NULL;
    temp->left = NULL;
    temp->data = data;
    return temp;
}

void push(STACK *st,NODE* item){
    if(st->top==MAX-1) return;
    else st->item[++(st->top)] = item;
}

NODE* pop(STACK *st){
    if(st->top==-1) return NULL;
    return st->item[(st->top)--];
}

int isempty(STACK* st){
    if(st->top==-1) return 1;
    return 0;
}

int prio(char c){
    switch(c){
        case '^' : return 3;
        case '*':
        case '/':return 2;
        case '+':
        case '-':return 1;
        default : return -1;
    }
}

NODE* converter(char *a){
    int n = strlen(a);
    STACK TS,OS;
    TS.top=-1;
    OS.top = -1;
    for(int i=0;i<n;i++){
        NODE* x = getNode(a[i]);
        if(isalnum(a[i])){
            push(&TS,x);
        }
        else if(a[i]=='('){
            push(&OS,x);
        }
        else if(a[i]==')'){
            while(!isempty(&OS) && (OS.item[OS.top])->data!='('){
                NODE* temp = getNode((OS.item[OS.top])->data);
                temp->right = pop(&TS);
                temp->left = pop(&TS);
                push(&TS,temp);
                pop(&OS);
            }
            pop(&OS);

        }
        else{
            while(!isempty(&OS) && prio((OS.item[OS.top])->data)>=prio(a[i])){
                NODE* temp = getNode((OS.item[OS.top])->data);
                temp->right = pop(&TS);
                temp->left = pop(&TS);
                push(&TS,temp);
                pop(&OS);
            }
            push(&OS,x);
        }

    }
    while(!isempty(&OS)){
         NODE* temp = getNode((OS.item[OS.top])->data);
                temp->right = pop(&TS);
                temp->left = pop(&TS);
                push(&TS,temp);
                pop(&OS);
    }
    return pop(&TS);
}

void disp(NODE* root){
    if(root==NULL) return;   // change this to any order of traversal
    printf("%c",root->data);
    disp(root->left);
    disp(root->right);
    
}

int main(){
    char a[100]= "(4+6)*2";
    NODE* root = converter(a);
    disp(root);
}
