#include<stdio.h>
#include<stdlib.h>
void countingSort(int arr[],int n){
    if(n<=1)    return;
    
    // find min and max value

    int max_val = arr[0];
    int min_val = arr[0];
    
    for(int i=1;i<n;i++){
        if(max_val<arr[i])    max_val = arr[i];
        if(min_val>arr[i])    min_val = arr[i];
    }
    
    //creating a counting arr;
    int range = max_val + min_val + 1;
    
    int *count = (int*) calloc(range,sizeof(int));
    int *output = (int*) calloc(n,sizeof(int));

    //count the values
    for(int i=0;i<n;i++){
        count[arr[i]-min_val]++;
    }

    //count the prefix sum
    for(int i=1;i<range;i++){
        count[i] = count[i]+count[i-1];
    }


    //build the output array 
    for(int i=n-1;i>=0;i--){
        int val = arr[i];
        int pos = count[val-min_val]-1;
        output[pos] = arr[i];
        count[val-min_val]--;
    }

    for(int i=0;i<n;i++){
        arr[i] = output[i];
    }
    free(count);
    free(output);
}


int main(){
    int arr[]= {4,5,3,9,0,2,5,7,9};
    int n = sizeof(arr)/sizeof(arr[0]);

    countingSort(arr,n);

    for(int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }

}