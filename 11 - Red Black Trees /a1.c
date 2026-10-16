#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    char color; // 0->red,1->red
    struct Node* left;
    struct Node* right;
    struct Node* parent;
}Node;

typedef struct RedBlackTree{
    struct Node* root;
    struct Node* NIL;
}RedBlackTree;

//initialize the red black tree
RedBlackTree* createTree(){
    RedBlackTree* tree = (RedBlackTree*)malloc(sizeof(RedBlackTree));
    tree->NIL = (Node*)malloc(sizeof(Node));
    tree->NIL->color = 1;
    tree->NIL->parent = tree->NIL;
    tree->NIL->left = tree->NIL;
    tree->NIL->right = tree->NIL; 

    tree->root = tree->NIL;
    return tree;
}

Node* createNode(int data){
    Node* node = (Node*)malloc(sizeof(Node));
    node->color = 0;
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->parent =NULL;
    return node;
}

//Search in RedBlackTree
Node* search_RBTree(RedBlackTree* tree,int data){
    Node* temp = tree->root;
    if(temp= tree->NIL) return tree->NIL;

    while(temp!=tree->NIL && temp->data!=data){
        if(data<temp->data){
            temp = temp->left;
        }
        else{
            temp = temp->right;
        }
    }
    return temp;

}
// Minimum in RedBlackTree
Node* minimum(RedBlackTree* tree){
    Node* temp = tree->root;

    if(temp = tree->NIL)    return temp;

    while(temp->left!=tree->NIL){
        temp = temp->left;
    }
    return temp;
}
// Maximum in RedBlackTree
Node* maximum(RedBlackTree* tree){
    Node* temp = tree->root;
    if(temp = tree->NIL)    return temp;
    while(temp->right != tree->NIL){
        temp = temp->right;
    }
    return temp;
}

void inorderTraversal(RedBlackTree* tree,Node* root){
    if(root == tree->NIL) return;

    inorderTraversal(tree,root->left);
    printf("[%d  %d] ",root->data,root->color);
    inorderTraversal(tree,root->right);
}


int main(){

}