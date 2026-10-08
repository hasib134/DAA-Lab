#include<stdio.h>

void merge(int arr[],int low,int mid,int high){
    int n = mid-low+1;
    int m = high-mid;

    int a1[n];
    int a2[m];
    for(int i =0;i<n;i++){
        a1[i] = arr[low+i]; 
    }

    for(int j=0;j<m;j++){
        a2[j] = arr[mid+j+1];
    }

    int i=0,j=0;
    int k =low;

    while(i<n && j<m){
        if(a1[i]<=a2[j]){
            arr[k] = a1[i];
            i++;
            k++;
        }
        else{
            arr[k] = a2[j];
            j++;
            k++;
        }
    }

    while(i<n){
        arr[k] = a1[i];
        i++;
        k++;
    }
    while(j<n){
        arr[k] = a2[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[] ,int low ,int high){
    if(low<high){
        int mid = low+ (high-low)/2;
        mergeSort(arr,low,mid);
        mergeSort(arr,mid+1,high);

        merge(arr,low,mid,high);
    }
}
int main(){
    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int n = sizeof(arr)/sizeof(arr[0]);
    mergeSort(arr,0,n-1);

    for(int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
}