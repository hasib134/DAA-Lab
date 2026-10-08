#include<stdio.h>
#include<stdlib.h>

int main(){
    int size;
    printf("Enter the size of array : \n");
    scanf("%d",&size);
    int *arr = (int*)(malloc(size*sizeof(int)));

    printf("Enter the elements of the array : \n");
    for(int i=0;i<size;i++){
        scanf("%d",&arr[i]);
    }

    for(int i=0;i<size;i++){
        printf("%d\t",arr[i]);
    }

}