#include<stdio.h>
#include<stdlib.h>

typedef struct{
    int *data;
    int size;
    int capacity;
}vector;

void vecInit(vector *v){
    v->capacity = 2;
    v->size = 0 ;
    v->data = (int*) malloc(v->capacity*sizeof(int));

    if(v->data == NULL) vecInit(v);
}

void vec_pushback(vector * v,int ele){

    if(v->size == v->capacity){
        //vector is full 
        // double the size of vector

        v->capacity *=2;
        v->data = (int*)realloc(v->data , v->capacity*sizeof(int));
    }
    v->data[v->size] = ele;
    v->size ++;
}

void free_vec(vector * v){
    free(v->data);
}

bool vec_pop(vector *v){
    if(v->size ==0) return false;

    v->size--;

}
int main(){
    vector v;
    vecInit(&v);
    vec_pushback(&v,10);

    printf("%d\n",v.data[0]);
}