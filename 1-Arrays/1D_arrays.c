#include<stdio.h>
int main(){
    //Array declaration 
     
    //1D arrays:
    int size ;
    printf("Enter the size of array : \n");
    scanf("%d",&size); 
    int arr[size]; // 1D Array


    printf("Enter the elements of the arrays :\n");

    for(int i=0;i<size;i++){
        scanf("%d",&arr[i]);
    }

    for(int i=0;i<size;i++){
        printf("%d\t",arr[i]);
    }

}