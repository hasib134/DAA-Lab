#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAXSIZE_QUEUE 256

struct node{
    int data;
    struct node* left;
    struct node* right;
};

struct queue{
    struct node* items[MAXSIZE_QUEUE];
    int front;
    int rear;
};

void initQueue(struct queue* q){
    q->front = -1;
    q->rear = -1;
}

bool isEmpty(struct queue* q){
    if(q->front ==-1 || q->front>q->rear)   return true;
    return false;
}

void enqueue(struct queue* q,struct node* treeNode){
    if(q->front ==-1){
        q->front =0;
    }
    q->rear ++;
    q->items[q->rear] = treeNode;
}

struct node* dequeue(struct queue* q){
    struct node* temp = q->items[q->front];
    q->front++;
    return temp;
}

struct node* createNode(int data){
    struct node* x = (struct node*)malloc(sizeof(struct node));
    x->data = data;
    x->left = NULL;
    x->right = NULL;

    return x;
}

struct node* BuildTree(){
    int val;
    printf("Enter the value of root , -1 for NULL value : ");
    scanf("%d",&val);
    if(val ==-1)    return NULL;

    struct node* root = createNode(val);

    struct queue q;
    initQueue(&q);
    enqueue(&q,root);

    while(!isEmpty(&q)){
        struct node* curr = dequeue(&q);

        //for left child
        int leftval;
        printf("Enter the value of left child of %d, -1 for NULL : ",curr->data);
        scanf("%d",&leftval);

        if(leftval!=-1){
            curr->left = createNode(leftval);
            enqueue(&q,curr->left);
        }

        //for right child
        int rightval;
        printf("Enter the value of right child of %d, -1 for NULL : ",curr->data);
        scanf("%d",&rightval);

        if(rightval!=-1){
            curr->right = createNode(rightval);
            enqueue(&q,curr->right);
        }
    }

    return root;
}

void levelOrderTraversal(struct node* root){
    if(root == NULL)    return ;
    struct queue q;
    initQueue(&q);
    enqueue(&q,root);

    while(!isEmpty(&q)){
        struct node* curr = dequeue(&q);
        printf("%d ",curr->data);
        if(curr->left!=NULL)    enqueue(&q,curr->left);
        if(curr->right!=NULL)    enqueue(&q,curr->right);
    }

}

int main(){
    //level order traversal
    struct node* root = BuildTree();
    levelOrderTraversal(root) ;
}