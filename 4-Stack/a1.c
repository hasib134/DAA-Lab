#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct node{
    int data;
    struct node* next;
};

struct node* createStack(){
    return NULL;
}

struct node* push(struct node* head,int ele){
    struct node* temp =malloc(sizeof(struct node));
    temp->data = ele;
    temp->next = head;
    head = temp;
    return head;
}

struct node* pop(struct node* head){
    if(head==NULL)  return NULL;
    if(head->next==NULL) {
        free(head);
        return NULL;
    }

    struct node* temp = head;
    head = head->next ;
    temp->next= NULL;
    free(temp);
    return head;
}

bool isempty(struct node* head){
    if(head==NULL)  return true;
    
    return false;
}

int size(struct node* head){
    struct node* temp =head;
    int len=0;

    while(temp){
        len++;
        temp = temp->next;
    }
    return len;
}

int main(){
    //stack :using LL
    
    //opeartion :
    /*
    1.push
    2.pop
    3.empty();
    4.size()
    */
}