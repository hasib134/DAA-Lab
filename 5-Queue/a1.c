#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct Node{
    int data;
    struct Node* next; 
}Node;

typedef struct{
    Node* front;
    Node* rear;
    int count; 
}Queue;

Queue* createQueue(){
    Queue *q = malloc(sizeof(Queue));
    if(q==NULL) return NULL;
    q->front = NULL;
    q->rear =NULL;
    q->count =0;
    return q;
}

void enqueue(Queue *q,int ele){
    if(q==NULL) return ;

    Node* temp = malloc(sizeof(Node));

    temp->data = ele;
    temp->next = NULL;

    if(q->rear==NULL){
        q->rear = temp;
        q->front = temp;
    }
    else{
        q->rear->next = temp;
        q->rear = temp;
    }
    q->count++;
}

int dequeue(Queue* q){
    if(q==NULL||q->front ==NULL)    return -1;
    
    Node* temp = q->front;
    int x = temp->data;
    q->front = q->front->next;
    free(temp);
    q->count--;
    return x;
}

int top(Queue * q){
    if(q==NULL||q->front ==NULL )   return -1;

    return q->front->data;

}

bool isempty(Queue *q){
    return (q==NULL||q->front==NULL);
}

int size(Queue *q){
    if(q==NULL) return 0;

    return q->count;
}
int main(){
    Queue *q =createQueue();
    enqueue(q,10);
    enqueue(q,20);
    enqueue(q,30);
    enqueue(q,40);

    printf("%d\n",top(q));
    printf("%d\n",size(q));
    printf("%d\n",isempty(q));

    dequeue(q);
    printf("%d\n",top(q));
    printf("%d\n",size(q));
    printf("%d\n",isempty(q));
    
}