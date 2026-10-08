#include<stdio.h>
int main(){
    //selection sort
    int n ; 
    scanf("%d",&n);

    int arr[n];
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }

    //selection sort
    //select minimum and place it and the end
    for(int i=0;i<n-1;i++){
        int min = arr[i];
        int min_idx = i;
        for(int j=i;j<n;j++){
            if(arr[j]<min){
                min = arr[j];
                min_idx = j;
            }
        }

        //only swap if min_idx!=i
        if(min_idx!=i){
            int temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
    }

    for(int i=0;i<n;i++){
        printf("%d\t",arr[i]);
    }
}