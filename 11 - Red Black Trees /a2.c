#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
    char color;
}Node;

typedef struct RBTree{
    Node* root;
    Node* nil;
}RBTree;

Node* createNode(RBTree* tree ,int data){
    Node* node = (Node*)malloc(sizeof(Node));
    node->left= tree->nil;
    node->right = tree->nil;
    node->parent = tree->nil;
    node->data = data;
    node->color = '0'; // by default color of the node is red
    return node;
}

RBTree* createTree(){
    RBTree* tree = (RBTree*)malloc(sizeof(RBTree));
    tree->nil = (Node*)malloc(sizeof(Node));
    tree->nil->parent =tree->nil;
    tree->nil->right = tree->nil;
    tree->nil->left = tree->nil;
    tree->nil->color = '1'; //default color of leaf node is black
    tree->root = tree->nil;
    return tree;
}

void leftRotate(RBTree* tree,Node* x){
    Node* y = x->right;
    x->right = y->left;
    if(y->left!=tree->nil){
        y->left->parent = x;
    }
    
    // case1 :  if x is root
    if(x->parent==tree->nil){
        tree->root = y;
    }
    else if(x == x->parent->left){
        x->parent->left = y;
    }
    else if(x==x->parent->right){
        x->parent->right = y;
    }

    y->parent = x->parent;
    y->left = x;
    x->parent = y;
}

void rightRotate(RBTree* tree,Node* x){
    Node* y = x->left;
    x->left = y->right;
    
    if(y->right !=tree->nil){
        y->right->parent = x;
    }

    if(x->parent == tree->nil){
        tree->root = y;
    }
    else if(x == x->parent->left){
        x->parent->left = y;
    }
    else if(x == x->parent->right){
        x->parent->right = y;
    }

    y->parent = x->parent;
    y->right = x;
    x->parent = y;
}

int main(){

}