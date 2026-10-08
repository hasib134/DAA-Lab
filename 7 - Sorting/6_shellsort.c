#include<stdio.h>

void shellSort(int *arr,int n){
    for(int gap = n/2 ; gap>0 ; gap = gap/2){
        for(int i=gap;i<n;i++){
            int j= i;
            int key = arr[i];

            while(j>=gap && arr[j-gap]>key){
                arr[j] = arr[j-gap];
                j = j-gap;
            }

            arr[j] = key;
        
        }
    }
}
int main(){
    //shell sort 
    int n;
    scanf("%d",&n);

    int arr[n];
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    
    shellSort(arr,n);
    
    for(int i=0;i<n;i++){
        printf("%d\t",arr[i]);
    }
}