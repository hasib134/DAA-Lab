#include<stdio.h>
int main(){
    int row,col;
    printf("Enter no of rows and col\n");
    scanf("%d %d",&row,&col);
    int arr[row][col];

    printf("Enter the elements of the array\n");
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            scanf("%d",&arr[i][j]);
        }
    }

    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            printf("%d\t",arr[i][j]);
        }
        printf("\n");
    }
}