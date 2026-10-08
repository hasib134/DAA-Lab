#include<stdio.h>

void merge(int *arr,int low,int mid,int high){
    int m = mid-low+1;
    int n = high - mid;
    int a1[m];
    int a2[n];

    for(int i=0;i<m;i++){
        a1[i] = arr[low+i]; 
    }

    for(int j=0;j<n;j++){
        a2[j] = arr[mid+j+1]; 
    }

    int i=0;
    int j=0;
    int k=low;

    while(i<m && j<n){
        if(a1[i]<a2[j]){
            arr[k] = a1[i];
            i++;
        }
        else{
            arr[k] = a2[j];
            j++;
        }
        k++;
    }

    while(i<m){
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

void merge_sort(int *arr,int low,int high){
    if(low<high){
        int mid = low+(high-low)/2;
        merge_sort(arr,low,mid);
        merge_sort(arr,mid+1,high);
        merge(arr,low,mid,high);
    }
    return;
}
int main(){
    int n;
    scanf("%d",&n);

    int arr[n];
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }

    merge_sort(arr,0,n-1);

    for(int i=0;i<n;i++){
        printf("%d",arr[i]);
    }



}