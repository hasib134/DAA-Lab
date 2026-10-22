#include<stdio.h>
#include<stdlib.h>

void swap(int arr[],int i ,int j){
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}


//insertion sort
void insertionSort(int arr[],int low,int high){
    for(int i=low+1;i<=high;i++){
        int key= arr[i];
        int j = i-1;
        while(j>=low && arr[j]>key){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

int partition(int arr[],int low ,int high){
    int pivot = arr[low];
    int i = low;
    int j = high;

    while(i<j){
        while(arr[i]<=pivot)    i++;
        while(arr[j]>pivot)     j--;

        if(i<j){
            swap(arr,i,j);
        }
    }
    swap(arr,low,j);
    return j;
}


int kthSmallestElement(int arr[],int low,int high,int key){
    int size = high-low+1;

    if(size<=5){
        insertionSort(arr,low,high);
        return arr[key];
    }
    
    //you have places all median in front 
    int no_of_groups = 0;
    for(int start = low;start<=high;start+=5){
        
        int end = start+4;
        if(end>high)    end = high;
        insertionSort(arr,start,end);
        int median_index = start + (end-start)/2;
        
        swap(arr,no_of_groups,start+median_index);
        no_of_groups++;
    }

    int pivot = kthSmallestElement(arr,low,low+no_of_groups-1,(no_of_groups-1)/2);

    int pivot_index = low;
    while(arr[pivot_index]!=pivot){
        pivot_index++;
    }
    
    swap(arr,low,pivot_index);

    int q = partition(arr,low,high);

    if(q == key){
        return arr[q];
    }
    else if(key<q){
        return kthSmallestElement(arr,low,q-1,key);
    }
    else{
        return kthSmallestElement(arr,q+1,high,key);
    }

}


int main(){

    int arr[] = {12, 3, 5, 7, 4, 19, 26, 23, 8, 15,
                    1, 9, 21, 11, 30, 17, 6, 14, 28, 2,
                    25, 10, 18, 13, 22};
    int n = sizeof(arr) / sizeof(arr[0]);

    int key = 13;

    int ele = kthSmallestElement(arr,0,n-1,key);
    printf("%d ", ele);
}