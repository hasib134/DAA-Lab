#include<stdio.h>
int partition(int *arr,int low,int high){
    int pivot = arr[low];
    int i=low;
    int j = high;
    while(i<j){
        while(arr[i]<=pivot && i<high){
            i++;
        }
        while(arr[j]>pivot && j>low){
            j--;
        }

        if(i<j){
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    //swap pivot with arr[j]
    int temp = arr[low];
    arr[low] = arr[j];
    arr[j] = temp;

    //return index of pivot
    return j;
}
void quick_sort(int *arr,int low,int high){
    if(low<high){
        int q = partition(arr,low,high);
        quick_sort(arr,low,q-1);
        quick_sort(arr,q+1,high);
    }
    return ;
}
int main(){
    //Quick sort

    int n;
    scanf("%d",&n);

    int arr[n];
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    quick_sort(arr,0,n-1);
    for(int i=0;i<n;i++){
        printf("%d\t",arr[i]);
    }
    
}