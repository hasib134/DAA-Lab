#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    int rank;
    struct Node* left;
    struct Node* right;
}Node;

Node* createNode(int data){
    Node* node = (Node*)malloc(sizeof(Node));
    node->left = NULL;
    node->right = NULL;
    node->rank = 1;
    node->data = data;
    return node;
}
int getRank(Node* node){
    if(node == NULL)    return 0;

    return node->rank;
}

Node* merge(Node* h1,Node* h2){
    //base case 
    if(h1 == NULL)  return h2;
    if(h2 == NULL) return h1;

    //make sure that value in h1 is greater than h2
    if(h1->data <h2->data){
        Node* temp = h1;
        h1 = h2;
        h2 = temp;
    }
    h1->right = merge(h1->right,h2);

    //check the rank 
    if(getRank(h1->left) < getRank(h1->right)){
        Node* temp = h1->left;
        h1->left = h1->right;
        h1->right = temp;
    }

    // update the rank
    h1->rank = 1 + getRank(h1->right);

    return h1;
}

Node* insert(Node* h1,int key){
    Node* newNode = createNode(key);
    
    return merge(h1,newNode);
}

void printHeap(Node* h1){
    if(h1 == NULL)  return ;

    Node* queue[100];
    int front = 0;
    int rear = 0;

    queue[rear++] = h1;
    
    while(front < rear){
        Node* temp = queue[front];
        printf("%d ",temp->data);
        front ++;
        if(temp->left){
            queue[rear] = temp->left;
            rear++;
        }
        if(temp->right){
            queue[rear] = temp->right;
            rear++;            
        }    
    }
    
}

int main(){
    int arr[] = {1,5,8,2,8,0,4,2};
    Node* root = NULL;
    int n = sizeof(arr)/sizeof(arr[0]);
    for(int i=0;i<n;i++){
        root = insert(root,arr[i]);
    }
    printHeap(root);
}
