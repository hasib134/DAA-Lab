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
    node->right = NULL;
    node->rank = 1;
    return node;
}
int getRank(Node* node){
    if(node ==NULL) return 0;

    return node->rank;
}

Node* merge(Node* h1,Node* h2){
    if(h1== NULL)   return h2;
    if(h2 == NULL)  return h1;

    //keep the data in h1 bigger than h2
    if(h1->data<h2->data){
        Node* temp = h1;
        h1 = h2;
        h2 = temp;
    }

    h1->right = merge(h1->right,h2);

    if(getRank(h1->left)<getRank(h1->right)){
        Node* temp = h1->left;
        h1->left = h1->right;
        h1->right = h1->left;
    }

    h1->rank = 1+getRank(h1->right);
    return h1;
}

Node* insert(Node* h1,int key){
    if(h1 == NULL)  return createNode(key);

    return merge(h1,createNode(key));
}

Node* extractMax(Node* h1){
    if(h1 == NULL)  return NULL;

    Node* left = h1->left;
    Node* right = h1->right;
    free(h1);
    return merge(left,right);
}


int max_value(Node* h1){
    if(h1 == NULL)  return -1;

    return h1->data;
}

int main(){

}