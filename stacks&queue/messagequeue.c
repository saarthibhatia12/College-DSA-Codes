#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 5

typedef struct queue{
    char item[MAX][20];
    int front,rear;
}QUEUE;

void ini(QUEUE *q){
    q->front = -1;
    q->rear = -1;
}

void send(QUEUE *q,char *a){
    if(q->rear==MAX-1){
        printf("\nQUEUE is full");
        return;
    }
    else if(q->front==-1){
        strcpy(q->item[++(q->front)],a);
        q->rear++;
    }
    else{
        strcpy(q->item[++(q->rear)],a);
    }
}

void recieve(QUEUE *q){
    if(q->front==-1){
        printf("\nQUEUE is empty..");
        return;
    }
    else{
        printf("\nThe message recieved is : %s ",q->item[(q->front)++]);
    }
    if(q->front>q->rear){
         q->front = -1;
        q->rear = -1;  
    }
}

void disp(QUEUE *q){
    if(q->front==-1){
        printf("\nQUEUE is empty..");
        return;
    }
    else{
        for(int i=q->front;i<=q->rear;i++){
            printf("\n%s\t",q->item[i]);
        }
    }
}

int main(){
    int choice = 0;
    QUEUE q;
    ini(&q);
    char msg[20];
    while(1){
        printf("\nENTER your choice : 1.SEND 2.RECIEVE 3.DISPLAY 4.EXIT : ");
        scanf("%d",&choice);
        switch(choice){
            case 1 : 
            
            printf("\nEnter your string : ");
            scanf("%s",msg);
            send(&q,msg);
            break;
            case 2 : 
            recieve(&q);
            break;
            case 3 : 
            disp(&q);
            break;
            case 4 : exit(0);
        }
    }
}
