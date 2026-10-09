#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct Node{
    int num_keys; // no of keys present in the node
    int keys[3]; // atmost 3 keys in the node 
    struct Node* child[4]; // atmost 4 child pointers in the node
    bool is_leaf; // is node a leaf node 
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

//Split function 
void* split(Node* parent ,int idx ){
    Node* full_child = parent->child[idx]; // node which is full 
    Node* sibling = createNode(full_child->is_leaf); // create the sibling of the node

    //split the node 
    sibling->keys[0] = full_child->keys[2];
    sibling->num_keys++;

    // if the node which is full is not a leaf node 
    if(!full_child->is_leaf){
        sibling->child[0] = full_child->child[2];
        sibling->child[1] = full_child->child[3];
        full_child->child[2]=NULL;
        full_child->child[3]=NULL;
    }

    // if it is the leaf node then ddont do anything
    full_child->num_keys = 1;

    //shift the child pointers 
    for(int i = parent->num_keys;i>=idx+1;i--){
        parent->child[i+1] = parent->child[i];
    }
    parent->child[idx+1] = sibling;

    //shift the keys in the parent
    for(int i = parent->num_keys-1;i>=idx;i--){
        parent->keys[i+1] = parent->keys[i];
    }
    parent->keys[idx] = full_child->keys[1];
    parent->num_keys++;
}

int main(){

}