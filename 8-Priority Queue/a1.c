#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


//dynamic arrays based implementation 
typedef struct PriorityQueue{
    int *data;
    int size;
    int capacity;
}PriorityQueue;

void swap(int *a , int *b){
    int t = *a;
    *a = *b;
    *b= t ;
}

PriorityQueue* createPQ(int capacity){
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->capacity = capacity;
    pq->size = 0;

    pq->data = (int*)malloc(sizeof(int)*pq->capacity);
    return pq;
}

void heapifyUp(PriorityQueue* pq, int index){
    int parent_index = (index -1)/2;

    while(index>0){
        if(pq->data[parent_index] < pq->data[index]){
            swap(&pq->data[parent_index],&pq->data[index]);
            index = parent_index;
        }
        else{
            break;
        }
    }
}

void heapifyDown(PriorityQueue* pq,int index){
    int l = 2*index+1;
    int r = 2*index+2;
    int largest = index;

    if(l < pq->size && pq->data[l]>pq->data[largest]){
        largest = l;
    }

    if(r<pq->size && pq->data[r]<pq->data[largest]){
        largest = r;
    }

    if(largest!=index){
        swap(&pq->data[index],&pq->data[largest]);
        heapifyDown(pq,largest);
    }
}

void * insert(PriorityQueue* pq,int val){
    if(pq->size == pq->capacity){
        pq->capacity = 2*pq->capacity;
        pq->data = (int*)realloc(pq->data,(sizeof(int))*pq->capacity);
    }

    pq->data[pq->size] = val;
    heapifyUp(pq,pq->size);
    pq->size++;
}

int max(PriorityQueue *pq){
    if(pq->size ==0)    return -1;

    return pq->data[0];
}

int extractMax(PriorityQueue* pq){
    if(pq->size ==0)    return -1;

    int max = pq->data[0];
    pq->data[0] = pq->data[pq->size-1];
    pq->size --;
    
    if(pq->size>0)  heapifyDown(pq,0);

    return max;
}


void delete(PriorityQueue *pq,int ele){
    if(pq->size ==0)    return;

    int i;
    for(i=0;i<pq->size;i++){
        if(pq->data[i] == ele){
            break;;
        }
    }
    pq->data[i] = pq->data[pq->size-1];
    pq->size -- ;
    if(pq->size >0) heapifyDown(pq,i);
}



int main(){

}