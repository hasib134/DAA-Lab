// randomized quicksort
#include<stdio.h>
#include<stdlib.h>

void swap(int *a,int *b){
    int temp = *a;
    *a =*b;
    *b = temp;
}

int partition(int arr[],int low,int high){
    int pivot = arr[low];
    int i = low;
    int j = high;

    while(i <j){
        while(arr[i]<=pivot)    i++;

        while(arr[j]>pivot)     j--;

        if(i<j){
            swap(&arr[i],&arr[j]);
        }
    }
    swap(&arr[low],&arr[j]);
    return j;
}

int randomizedPartition(int arr[],int low,int high){
    int randomIndex = low + rand()%(high-low+1);
    swap(&arr[low],&arr[randomIndex]);
    return partition(arr,low,high);
}

void randomizedQuickSort(int arr[],int low,int high){
    if(low<high){
        int q = randomizedPartition(arr,low,high);
        randomizedQuickSort(arr,low,q-1);
        randomizedQuickSort(arr,q+1,high);
    }
}

int main(){
int arr[] = {9,8,7,6,5,4,3,2,1};
    int n = sizeof(arr)/sizeof(arr[0]);
    randomizedQuickSort(arr,0,n-1);
    for(int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
}