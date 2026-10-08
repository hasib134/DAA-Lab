#include<stdio.h>
#include<stdlib.h>

void countingSort(int arr[],int n,int exp){
    int count[10]={0}; //0-9 digits 
    int output[n]; // storing the output 

    //count the numbers according to the digits

    for(int i=0;i<n;i++){
        int digit = (arr[i]/exp)%10;
        count[digit]++;
    }

    //find cumulative sum
    for(int i=1;i<10;i++){
        count[i]+=count[i-1];
    }


    //build the output array in reverse
    for(int i=n-1;i>=0;i--){
        int digit = (arr[i]/exp)%10;
        int pos = count[digit]-1;
        output[pos] = arr[i];
        count[digit]--;
    }

    for(int i=0;i<n;i++){
        arr[i] = output[i];
    }

}

void radixSort(int arr[],int n){
    if(n<=1)    return ;

    // find the maximum no to know the digits;
    int max_val = arr[0];
    for(int i=1;i<n;i++){
        if(max_val<arr[i])  max_val = arr[i];
    }

    //run the counting sort for every digit position
    for(int exp = 1;(max_val/exp)>0;exp*=10){
        countingSort(arr,n,exp);
    }
}

int main(){
    int arr[]={170, 45, 75, 90, 802, 24, 2, 66};
    int n = sizeof(arr)/sizeof(arr[0]);

    radixSort(arr,n);

    for(int i=0;i<n;i++){
        printf("%d ",arr[i]); 
    }
}