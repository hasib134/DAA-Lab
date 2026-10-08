#include<stdio.h>
int binarySearch(int *arr,int low,int high,int ele){
    while(low<=high){
        int mid = low+(high-low)/2;

        if(arr[mid]>=ele){
            high = mid-1;
        }
        else{
            low = mid+1;
        }
    }
    return low; // return the index
}
int main(){
    int n;
    scanf("%d",&n);
    
    int arr[n];

    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }

    for(int i=1;i<n;i++){
        int key = arr[i];
        int j = i-1;

        int index = binarySearch(arr,0,j,key);
        while(j>=index ){
            arr[j+1] = arr[j];
            j--;
        }
        arr[index] = key;
    }


    for(int i=0;i<n;i++){
        printf("%d\t",arr[i]);
    }

}