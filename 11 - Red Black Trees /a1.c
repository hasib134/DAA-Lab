#include<stdio.h>
#include<stdlib.h>

//0 -> red color
//1 -> black color

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
    node->data = data;
    node->left = tree->nil;
    node->right = tree->nil;
    node->parent= tree->nil;
    node->color = '0';
    return node;
}

RBTree* createTree(){
    RBTree* tree = (RBTree*)malloc(sizeof(RBTree));
    tree->nil = (Node*)malloc(sizeof(Node));
    tree->nil->parent = tree->nil;
    tree->nil->left = tree->nil;
    tree->nil->right = tree->nil;
    tree->nil->color = '1';

    tree->root = tree->nil;

    return tree;
}