#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct {
    int * data;
    int front;
    int rear;
    int capacity;
    int size;
}Queue;

Queue * createQueue(int size){
    Queue * q = malloc(sizeof(Queue));
    q->capacity=size;
    q->size =0;
    q->data = malloc(sizeof(int)*q->capacity);
    q->front=0;
    q->rear = -1;
    return q;
}

void enqueue(Queue *q,int ele){
    if(q==NULL) return ;

    if(q->size == q->capacity){
        int new_capacity = q->capacity *2;
        int *new_data= malloc(new_capacity*sizeof(int));
        
        for(int i=0;i<q->size;i++){
            new_data[i] = q->data[(q->front+i)%q->capacity];
        }

        free(q->data);
        q->capacity = new_capacity;
        q->data = new_data;
        q->front =0;
        q->rear = q->size-1;

    }

    q->rear = (q->rear+1)%q->capacity;
    q->data[q->rear]=ele;
    q->size ++;

}
bool isempty(Queue *q){
    return(q==NULL || q->size==0);

}
int size(Queue* q){
    if(q==NULL) return 0;

    return q->size;
}
int dequeue(Queue *q){
    if(isempty(q)){
        return -1;
    }
    int val = q->data[q->front];
    q->front = (q->front+1)%q->capacity;
    q->size--;

    return val;
}

int peek(Queue* q){
    if(q==NULL|| q->size ==0)   return -1;

    return q->data[q->front];
}

bool deleteQueue(Queue *q){
    if(q){
        free(q->data);
        free(q);
    }
}
int main(){
    Queue *q = createQueue(2);

    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30); // Triggers resizing: capacity doubles from 2 -> 4

    printf("Front element: %d\n", peek(q));    
    printf("Queue size: %d\n", size(q));       

    printf("Dequeued: %d\n", dequeue(q));      
    printf("Dequeued: %d\n", dequeue(q));      

    printf("New Front: %d\n", peek(q));        
    printf("Remaining size: %d\n", size(q));   
}