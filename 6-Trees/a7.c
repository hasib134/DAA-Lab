#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAX_QUEUE_SIZE 256

//here we will use the queue 

typedef struct treeNode{
    int data;
    struct treeNode* left;
    struct treeNode* right;
}treeNode;

treeNode* createNode(int data){
    treeNode* node = (treeNode*)malloc(sizeof(treeNode));

    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

typedef struct {
    treeNode * items[MAX_QUEUE_SIZE];
    int front;
    int rear;
}Queue;

void initQueue(Queue* q){
    q->front = -1;
    q->rear = -1;
}

void enqueue(Queue* q,treeNode * node){
    if(q->front ==-1){
        q->front = 0;
    }
    q->rear++;
    q->items[q->rear] = node;
}

treeNode* dequeue(Queue* q){
    treeNode* temp = q->items[q->front];
    q->front++;
    return temp;
}

bool isEmpty(Queue* q){
    return (q->front == -1 || q->front>q->rear);
}

treeNode* builTree(){
    int val;
    printf("Enter the root value and -1 for NULL: ");
    scanf("%d",&val);
    if(val == -1)   return NULL;

    treeNode* root = createNode(val);
    Queue q ; 
    initQueue(&q);
    enqueue(&q,root);
    while(!isEmpty(&q)){
        treeNode* curr = dequeue(&q);
        
        //for left child
        int leftchild;
        printf("Enter the value of left child of %d ",curr->data);
        scanf("%d",&leftchild);
        if(leftchild!=-1){
            curr->left = createNode(leftchild); 
            enqueue(&q,curr->left);
        }

        // for right child 
        int rightchild;
        printf("Enter the value of right child of %d ",curr->data);
        scanf("%d",&rightchild);
        if(rightchild!=-1){
            curr->right = createNode(rightchild); 
            enqueue(&q,curr->right);
        }   
    }
    return root;
}

void inorder(treeNode* root){
    if(root ==NULL) return ;

    inorder(root->left);
    printf("%d ",root->data);
    inorder(root->right);
}

int main(){
    //create a binary tree from array 
    treeNode* root = builTree();

    inorder(root);

}