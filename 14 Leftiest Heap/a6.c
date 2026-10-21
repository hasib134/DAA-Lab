#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    struct Node* left;
    struct Node* right;
    int rank;
}Node;


Node* createNode(int data){
    Node* node= (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = NULL;
    node->right= NULL;
    node->rank =1;
    return node; 
}

int getRank(Node* node){
    if(node == NULL)    return 0;

    return node->rank;
}

Node* merge(Node* h1,Node* h2){
    if(h1 == NULL)  return h2;
    if(h2 == NULL)  return h1;


    if(h1->data<h2->data){
        Node* temp = h1;
        h1 = h2;
        h2 = temp;
    }

    h1->right = merge(h1->right,h2);

    if(getRank(h1->left)<getRank(h1->right)){
        Node* temp = h1->left;
        h1->left = h1->right;
        h1->right = temp;
    }
    h1->rank = 1 + getRank(h1->right);
    return h1; 
}

typedef struct Queue{
    Node **data;
    int front;
    int rear;
    int size;
    int capacity;
}Queue;

Queue* createQueue(int capacity){
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->size = 0;
    queue->front = 0;
    queue->rear = 0;
    queue->data = (Node**)malloc(queue->capacity*sizeof(Node));
    return queue;
}

void enqueue(Queue* queue,Node* node){
    queue->data[queue->rear] = node;
    queue->rear = (queue->rear+1)%queue->capacity;
    queue->size++;
}

Node* dequeue(Queue* queue){
    Node* node = queue->data[queue->front];
    queue->front = (queue->front+1)%queue->capacity;
    queue->size--;
    return node;
}

Node* buildHeap(int arr[],int n ){

    if(n<=0) return NULL;
    Queue* queue = createQueue(n);

    for(int i=0;i<n;i++){
        enqueue(queue,createNode(arr[i]));
    }
    while(queue->size>1){
        Node* node1 = dequeue(queue);
        Node* node2 = dequeue(queue);
        enqueue(queue, merge(node1,node2));
    }
    Node* root = dequeue(queue);
    free(queue->data);
    free(queue);
    return root;
}

void preorderTraversal(Node* root){
    if(root == NULL)    return ;

    printf("[%d %d] ",root->data,root->rank);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

int main(){
    int arr[] = {4, 10, 3, 5, 1, 15, 20, 8};

    int n = sizeof(arr)/sizeof(arr[0]);

    Node* root = buildHeap(arr,n);
    preorderTraversal(root);
}