#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    struct Node* left;
    struct Node* right;
    int key;
    char is_end;
}Node;

Node* createNode(){
    Node* node =(Node*)malloc(sizeof(Node));
    node->left = NULL;
    node->right =NULL;
    node->is_end = '0';
    node->key = 0;
    return node;
}

Node* insert(int key){

}

int main(){

}