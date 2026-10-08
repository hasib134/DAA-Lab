#include<stdio.h>
#include<stdlib.h>

struct node{
    int data;
    struct node* next;
};

struct node* createnode(int data){
    struct node* x = (struct node*)malloc(sizeof(struct node));
    x->data = data;
    x->next = NULL;
    return x;
}

struct node* createLL(int arr[],int n){
    struct node* head = createnode(arr[0]);
    struct node* temp = head;

    for(int i=1;i<n;i++){
        temp->next =createnode(arr[i]);
        temp = temp->next; 
    }
    return head;
}
struct node* merge(struct node* a,struct node*b){
    
    struct node* c;
    
    if(a->data <= b->data){
        c=a;
        a=a->next;        
    }
    else{
        c=  b;
        b=b->next;
    }
    struct node* temp = c;

    while(a!=NULL && b!=NULL){
        if(a->data <= b->data){
            c->next = a;
            c= c->next;
            a = a->next;        
        }
        else{
            c->next = b;
            c= c->next;
            b=b->next;
        }
    }
    if(a!=NULL){
        c->next = a;
    }
    if(b!=NULL){
        c->next = b;
    }
    return temp;
}

struct node* findMiddle(struct node* head){
    struct node* slow = head;
    struct node* fast = head->next;
    while(fast!=NULL && fast->next!=NULL){
        fast = fast->next->next;
        slow = slow->next;
    }

    return slow;

}
struct node* mergeSort(struct node* head){
    
    if(head == NULL || head->next ==NULL)   return head ;

    struct node* temp = head;

    //find the middle of the LL 
    struct node* middle = findMiddle(head);
    
    struct node* leftHead = head;
    struct node* rightHead = middle->next;
    middle->next = NULL;

    leftHead = mergeSort(leftHead);
    rightHead = mergeSort(rightHead);

    return merge(leftHead,rightHead);

}

void printLL(struct node* head ){
    if(head ==NULL)  return ;
    struct node* temp = head;
    while(temp!=NULL){
        printf("%d ",temp->data);
        temp = temp->next;
    }
}

int main(){
    //merge sort on LL
    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int n = sizeof(arr)/sizeof(arr[0]);
    struct node* head = createLL(arr,n);
    head = mergeSort(head);

    printLL(head);

}