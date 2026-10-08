#include<stdio.h>
#include<stdlib.h>

struct node{
    int data;
    struct node* left;
    struct node* right;
};

struct node* createNode(int value){
    struct node* x = (struct node*) malloc(sizeof(struct node));

    if(x==NULL){
        printf("Memory allocation falied");
        exit(1);
    }

    x->data = value;
    x->left = NULL;
    x->right = NULL;

    return x; 
}

void inorder(struct node* root){
    if(root == NULL){
        return ;
    }
    inorder(root->left);
    printf("%d ",root->data);
    inorder(root->right);
}

void preoder(struct node* root){
    if(root==NULL){
        return;
    }
    printf("%d ",root->data);
    preoder(root->left);
    preoder(root->right);
}

void postoder(struct node* root){
    if(root==NULL){
        return ;
    }
    postoder(root->left);
    postoder(root->right);
    printf("%d ",root->data);
}

int main(){
    // Tree traversal

    struct node* root = createNode(1);
    
    root->left = createNode(2);
    root->right = createNode(3);
    
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    inorder(root);
    printf("\n");

    preoder(root);
    printf("\n");

    postoder(root);
    printf("\n");
}