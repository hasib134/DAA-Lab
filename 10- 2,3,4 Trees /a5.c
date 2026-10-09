#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

// Delete Function 

typedef struct Node{
    int num_keys;
    int keys[3];
    struct Node* child[4];
    bool is_leaf;
}Node;

Node* createNode(bool is_leaf){
    Node* node = (Node*)malloc(sizeof(Node));
    node->num_keys = 0;
    node->is_leaf = is_leaf;

    for(int i=0;i<4;i++){
        node->child[i] = NULL;
    }
    return node;
}




int main(){

}