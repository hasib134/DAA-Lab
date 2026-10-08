#include<stdio.h>
#include<stdlib.h>

struct Mybox{
    int *data; //keep the ointer to dynamic array
    int size; // keep track of no of elements in the array
    int capacity;   //how many items fit here before we need extra space
};


int main(){
    //implement vectors from scratch
    // Step 1 : define structure

    struct Mybox v1;
    v1.size =0;
    v1.capacity = 2;

    v1.data = malloc(v1.size*sizeof(int));
    
    //check if we have got memory from computer
    if(v1.data == NULL){
        printf("error\n");
        return 0;
    }

    for(int i=0;i<=5;i++){
        if(v1.size == v1.capacity){
            //if the capacity is full then double the capacity of the arrays 
            // here we will use realloc function    
            v1.capacity *= 2;
            v1.data = realloc(v1.data , v1.capacity*sizeof(int));
        }
        v1.data[v1.size] = i*10;
        v1.size++;
    }

    for(int i=0;i<=5;i++){
        printf("%d ",v1.data[i]);
    }
    
}