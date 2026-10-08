#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct{
    int* data;
    int capcity;
    int top;
} stack;

stack * createStack(int size){
    stack *st = malloc(sizeof(stack));  
    st->capcity=size;
    st->data = malloc(st->capcity * sizeof(int));
    st->top = -1;
    return st;
}

void push(stack *st,int ele){
    if(st->top==st->capcity-1){
        st->capcity *=2;
        st->data = realloc(st->data , st->capcity*sizeof(int));
    }

    st->top++;
    st->data[st->top] = ele;
}

void pop(stack* s){
    if(s->top ==-1) return ;

    s->top --;
}

int top(stack *s){
    if(s->top==-1)  return -1;

    return s->data[s->top];
}

bool isempty(stack * s){
    if(s->top==-1)  return true;
    return false;
}

int size(stack * s){
    if(s==NULL ||s->top ==-1) return 0;
    return s->top+1;
}

void freeStack(stack * s){
    if(s!=NULL){
        free(s->data);
        free(s);
    }
}
int main(){
    //stack using synammic arrays

    stack * s = createStack(5);
    push(s,10);
    push(s,20);
    push(s,30);

    printf("%d\n",top(s));
    printf("%d\n",size(s));
    printf("%d\n",isempty(s));

    
}