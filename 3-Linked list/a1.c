#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    struct node* next;
};

struct node* createSLL(int *arr,int size){
    struct node* head = (malloc(sizeof(struct node)));
    if(size == 1){
        head->data = arr[0];
        head->next = NULL;
        return head;
    }
    head->data = arr[0];
    head->next = NULL;
    struct node* temp = head;
    for(int i=1;i<size;i++){
        struct node* x = malloc(sizeof(struct node));
        x->data = arr[i];
        temp->next = x;
        temp = temp->next;
        x->next =NULL;
    }
    return head;
}
void printSLL(struct node* head){
    if(head ==NULL) return ;

    struct node* temp = head;
    while(temp){
        printf("%d ",temp->data);
        temp = temp->next;
    }
    printf("\n");
}

//insert in SLL
struct node* insertHead(struct node* head,int ele){
    struct node* x = malloc(sizeof(struct node));
    x->data = ele;
    x->next = NULL;
    if(head ==NULL){
        head = x;
        return head;
    }

    x->next = head;
    head = x;
    return head;
}   
struct node* insertTail(struct node* head,int ele){
    struct node*x = malloc(sizeof(int));
    x->data = ele;
    x->next = NULL;
    if(head ==NULL) return x;

    struct node* temp = head;
    while(temp->next)   temp = temp->next;

    temp->next = x;
    return head;
}

struct node* insertAtPosition(struct node* head,int ele,int pos){
    struct node* x = malloc(sizeof(struct node));
    x->data = ele;
    x->next = NULL;
    if(head ==NULL){
        return x;
    }
    int i=1;
    struct node* temp =head;
    while(temp!=NULL && i<pos){
        temp = temp->next ;
        i++;
    }
    x->next  = temp->next ;
    temp->next = x;
    return head;

}

// deletion in SLL 
struct node* deleteHead(struct node* head){
    if(head == NULL || head->next ==NULL)    return NULL;
    struct node* temp = head;
    head = head->next ;

    free(temp);
    return head;
}

struct node* deleteTail(struct node* head){
    if(head == NULL || head->next ==NULL){
        return NULL;
    }

    struct node* temp = head;
    while(temp->next->next){
        temp = temp->next;
    }
    struct node* x = temp->next;
    free(x);
    temp->next = NULL;
    return head;
}   

struct node* deletePos(struct node* head,int pos){
    if(head ==NULL )    return NULL;

    struct node* temp = head;
    if(pos ==1){
        head = head->next;
        free(temp);
        return head;
    }

    int i=1;
    while(temp && i<pos){
        i++;
        temp = temp->next;
    }
    struct node*x = temp->next;
    temp->next = temp->next->next;
    free(x);
    return head;
}

//find size of SLL 

int sizeSLL(struct node* head){
    if(head == NULL)    return 0;

    if(head->next ==NULL)   return 1;

    struct node* temp = head;
    int len =0;
    while(temp){
        len++;
        temp = temp->next;
    }
    return len;
}

int main(){
    int arr[5] = {1,2,3,4,5};
    struct node* head = createSLL(arr,5);
    printSLL(head);

    head = insertHead(head,100);
    printSLL(head);

    head = insertTail(head,200);
    printSLL(head);

    head = insertAtPosition(head,300,2);
    printSLL(head);

    head = deleteHead(head);
    printSLL(head);

    head =deleteTail(head);
    printSLL(head);

    head = deletePos(head,2);
    printSLL(head);

    int len = sizeSLL(head);
    printf("%d\n",len);

}