#include<stdio.h>
#include<stdlib.h>

struct node{
    int data;
    struct node* left;
    struct node* right;  
};

struct node* createNode(int data){
    //create the node and return the node 
    struct node* newNode = (struct node* )malloc(sizeof(struct node));
    
    if(newNode == NULL){
        printf("Memory allocation failed");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}
int main(){
    //Tree Traversal 

    struct node* root = createNode(1);
    
    root->left = createNode(2);
    root->right = createNode(3);

    root->left->left = createNode(4);
    root->right->right = createNode(5);
    
    printf("%d ",root->data);
}