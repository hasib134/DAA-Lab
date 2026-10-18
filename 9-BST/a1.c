#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
}Node;

Node* createNode(int data){
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = NULL;
    node->parent = NULL;
    node->right = NULL;

    return node;
}

typedef struct Tree{
    Node* root ;
}Tree;

Tree* createTree(){
    Tree* tree = (Tree*)malloc(sizeof(Tree));
    tree->root =NULL;
    return tree;
} 

void insertBST(Tree* tree,int data){
    Node* newNode = createNode(data);
    if(tree->root == NULL){
        tree->root = newNode;
        return;
    }
    Node* curr = tree->root;
    Node* parent = NULL;
    
    while(curr!=NULL){
        parent = curr;
        if(data <= curr->data){
            curr = curr->left;
        }
        else{
            curr = curr->right;
        }
    }
    newNode->parent = parent;
    if(data <= parent->data){
        parent->left = newNode;
    }
    else{
        parent->right= newNode;
    }
    return ;
}

void inorder(Node* root ){
    if(root == NULL)  return ;
    
    inorder(root->left);
    printf("%d ",root->data);
    inorder(root->right);
}

int main(){
    Tree* myTree = createTree();

    insertBST(myTree, 50);
    insertBST(myTree, 30);
    insertBST(myTree, 70);
    insertBST(myTree, 20);
    insertBST(myTree, 40);

    inorder(myTree->root);
    
}