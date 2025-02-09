#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#define MAX 100

typedef struct stack{
    int top;
    char item[MAX];
}STACK;

void push(STACK *st,char ele){
    if(st->top==MAX-1) return;
    st->item[++(st->top)] = ele;
}

void pop(STACK *st){
    if(st->top==-1) return;
    st->top--;
}

int isempty(STACK *st){
    if(st->top==-1) return 1;
    else return 0;
}

void ini(STACK *st){
    st->top=-1;
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

void reverse(char *a){
    int n = strlen(a);
    int start = 0;
    int end = n-1;
    while(start<end){
        char temp = a[start];
        a[start] = a[end];
        a[end] = temp;
        start++;
        end--;
    }
}

void conv(char *s){
    STACK st;
    ini(&st);
    char ans[MAX] = "";
    int k = 0;
    int n = strlen(s);
    reverse(s);
    for(int i=0;i<n;i++){
        if((s[i]>='a'&&s[i]<='z')||(s[i]>='A'&&s[i]<='Z')||(s[i]>='0'&&s[i]<='9')){
            ans[k++] = s[i];
        }
        else if(s[i]==')'){
            push(&st,s[i]);
        }
        else if(s[i]=='('){
            while(!isempty(&st)&&st.item[st.top]!=')'){
                ans[k++] = st.item[st.top];
                pop(&st);
            }
            pop(&st);
        }
        else{
            while(!isempty(&st)&&prio(st.item[st.top])>prio(s[i])){
                ans[k++] = st.item[st.top];
                pop(&st);
            }
            push(&st,s[i]);
        }
    }
    while(!isempty(&st)){
        ans[k++]=st.item[st.top];
        pop(&st);
    }
    reverse(ans);
    printf("%s",ans);
}

int main(){
    char s[100] = "-K+L-M*N+(0^P)*W/U/V*T+Q";
    conv(s);
}
