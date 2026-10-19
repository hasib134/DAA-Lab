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
    node->data = data;
    node->left = NULL;
    node->rank = NULL;
    node->rank = 1;
    return node;
}


Node* merge(Node* h1,Node* h2){
    if(h1 == NULL)  return h2;
    if(h2 == NULL)  return h1;

    //firstly ensure that value in h1 is always greater than h2
    if(h1->data<h2->data){
        Node* temp = h1;
        h1 = h2;
        h2= temp;
    }

    //recusively do it 
    h1->right = merge(h1->right,h2);

    if(h1->left->rank < h1->right->rank){
        Node* temp = h1->left;
        h1->left = h1->right;
        h1->rank = temp;
    }

    //we are always ensuring that rank of right child is less
    h1->rank = 1 + h1->right->rank;

    return h1;
}

int main(){

}