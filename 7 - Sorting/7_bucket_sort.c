#include<stdio.h>
#include<stdlib.h>

//to store elements in bucket we will use dynamic array
typedef struct{
    float *data;
    int size;
    int capacity;
}Bucket;

//this will insert data in the bucket
void push_element_toBucket(Bucket *b,float val){
    if(b->size == b->capacity){
        if(b->capacity ==0){
            b->capacity = 2;
        }
        else{
            b->capacity *=2;
        }

        b->data = realloc(b->data,b->capacity*sizeof(float));
    }

    b->data[b->size] = val;
    b->size++;

}

void insertionSort(float *arr,int size){

    for(int i = 1;i<size;i++){
        float key  = arr[i];
        int j = i-1;
        while(j>=0 && arr[j]>key){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

void bucketSort(float *arr,int n){
    if(n<=1)    return;

    //initialize n buckets 
    Bucket *bucket = (Bucket*)calloc(n,sizeof(Bucket));
    //initial assign all values to 0

    //scatter the elements in the bucket
    for(int i=0;i<n;i++){
        int bucIdx = (int)(n*arr[i]);
        if(bucIdx>=n){
            bucIdx = n-1;
        }
        push_element_toBucket(&bucket[bucIdx],arr[i]);
    }

    //sort elements in every bucket using insertion sort
    for(int i=0;i<n;i++){
        if(bucket[i].size >1){
            insertionSort(bucket[i].data,bucket[i].size);
        }
    }

    //gather all the data

    int index = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<bucket[i].size;j++){
            arr[index]=bucket[i].data[j];
            index++;
        }
        free(bucket[i].data);
    }
    free(bucket);

}

int main(){
    //bucket sort
    float arr[] = {0.78, 0.17, 0.39, 0.26, 0.72, 0.94, 0.21};
    int n = sizeof(arr)/sizeof(arr[0]);

    bucketSort(arr,n);

    for(int i=0;i<n;i++){
        printf("%0.3f\t",arr[i]);
    }
}