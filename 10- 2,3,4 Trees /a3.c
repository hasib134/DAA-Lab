#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct Node{
    int key[3];
    int num_keys;
    struct Node* child[4];
    bool is_leaf;
}Node;

Node* createNode(bool is_leaf){
    Node* node = (Node*)malloc(sizeof(Node));
    node->is_leaf = is_leaf;
    node->num_keys = 0;
    for(int i=0;i<4;i++){
        node->child[i] = NULL;
    }
    return node;
}

//inorder Traversal :

void inorder(Node* root){
    if(!root)   return;

    for(int i=0;i<root->num_keys;i++){
        if(!root->is_leaf){
            inorder(root->child[i]);
        }
        printf(root->key[i]);
    }

    if(!root->is_leaf){
        inorder(root->child[root->num_keys]);
    }

}

//search in a node
bool search(Node* root , int key){
    if(!root)   return false;

    int i =0 ;
    while(i<root->num_keys && key>root->key[i]){
        i++;
    }
    if(i<root->num_keys && key == root->key[i]){
        return true;
    }
    if(root->is_leaf){
        return false;
    }
    return search(root->child[i],key);
}

int main(){

}