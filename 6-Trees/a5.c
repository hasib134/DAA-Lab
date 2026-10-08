#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct node{
    int data;
    struct node* left;
    struct node* right;
};

// here we are using queue using linked list 

struct Qnode{
    struct node* treeNode ; 
    struct Qnode* next ;
};

struct queue{
    struct Qnode* front ; 
    struct Qnode* rear ;
};


struct node* createNode(int data){
    struct node* x = (struct node*)malloc(sizeof(struct node));
    
    x->data = data;
    x->left = NULL;
    x->right = NULL;
    return x ; 

}

struct queue* createQueue(){
    struct queue *q = (struct queue*)malloc(sizeof(struct queue));
    q->front = NULL;
    q->rear = NULL;

    return q;
}

void enqueue(struct queue* q,struct node* treeNode){
    struct Qnode* x = (struct Qnode*)malloc(sizeof(struct Qnode));
    x->treeNode = treeNode;
    x->next = NULL;

    if(q->rear == NULL){
        q->front =x;
        q->rear = x;
        return ;
    }

    q->rear->next = x;
    q->rear = x;
}

struct node* dequeue(struct queue* q){
    if(q->front == NULL)    return NULL ;
    struct Qnode* temp = q->front;
    struct node* treenode = temp->treeNode;
    q->front = q->front->next;
    if(q->front == NULL){
        q->rear =NULL;
    }
    free(temp);

    return treenode;
}

bool isQueueEmpty(struct queue* q){
    return (q->front == NULL);

}
struct node* buildTree(int arr[],int n ){
    if(n==0 || arr[0] ==-1) return NULL;

    struct queue* q = createQueue();

    struct node* root = createNode(arr[0]);
    enqueue(q, root);
    
    int i =1;
    while(!isQueueEmpty(q) && i<n){
        struct node * temp = dequeue(q);

        //check for left child
        if(i<n){
            if(arr[i]!=-1){
                struct node * leftchild = createNode(arr[i]);
                temp->left = leftchild;
                enqueue(q,leftchild);
            }
            i++;
        }

        //check for right child
        if(i<n){
            if(arr[i]!=-1){
                struct node* rightchild = createNode(arr[i]);
                temp->right = rightchild;
                enqueue(q,rightchild);
            }
            i++;
        }
    }
    return root;
}

void inorder(struct node* root){
    if(root == NULL)    return ;

    inorder(root->left);
    printf("%d ",root->data);
    inorder(root->right);
}



int main(){
    // level order traversal of binary tree
    int arr[] = {1,2,3,-1,4,-1,5};
    int n = sizeof(arr)/sizeof(arr[0]);
    struct node* root = buildTree(arr,n);

    inorder(root);

     
}