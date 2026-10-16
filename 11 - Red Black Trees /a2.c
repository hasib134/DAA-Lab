#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
    char color;
}Node;

typedef struct RedBlackTree{
    struct Node* root;
    struct Node* NIL;
}RedBlackTree;

RedBlackTree* createTree(){
    RedBlackTree* tree = (RedBlackTree*)malloc(sizeof(RedBlackTree));
    tree->NIL = (Node*)malloc(sizeof(Node));
    tree->NIL->color = 1;
    tree->NIL->parent = tree->NIL;
    tree->NIL->right = tree->NIL;
    tree->NIL->left = tree->NIL;
    tree->root = tree->NIL;

    return tree;
}

Node* createNode(int data){
    Node* node = (Node*)malloc(sizeof(Node));
    node->color = 0;
    node->parent = NULL;
    node->left= NULL;
    node->right = NULL;
    node->data = data;
    return node;
}

void inorder(RedBlackTree* tree,Node* root){
    if(root == tree->NIL)   return;
    
    inorder(tree,root->left);
    printf("[%d %d]\t",root->data,root->color);
    inorder(tree,root->right);
}

//Successor of node in Red Black Tree
Node* successor(RedBlackTree* tree,Node* root){
    if(root==tree->NIL) return root;

    Node* temp = root;
    while(temp->left!=tree->NIL){
        temp = temp->left;
    }
    return temp;
}

//Predecessor 
Node* predecessor(RedBlackTree* tree,Node* root){
    if(root == tree->NIL)   return root;

    Node* temp = root;
    while(temp->right!=tree->NIL){
        temp = temp->right;
    }
    return temp;
}

int main(){

}