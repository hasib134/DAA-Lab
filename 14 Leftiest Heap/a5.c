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
    node->data = data;
    node->rank =1 ;
    return node;
}

int getRank(Node* h1){
    if(h1 == NULL)  return 0;

    return h1->rank;
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
        Node* temp  = h1->left;
        h1->left = h1->right ;
        h1->right = temp;
    }
    h1->rank = 1 +  getRank(h1->right);
    return h1; 
}

Node* insert(Node* h1,int key){
    Node* newNode = createNode(key);

    return merge(h1,newNode);
}

int main(){
    
}
