#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    struct Node* left;
    struct Node* right;
    int val;
    char is_end_node;
}Node;

typedef struct Trie{
    Node* root;
    int key;
}Trie;

Node* createNode(){
    Node* node =(Node*)malloc(sizeof(Node));
    node->left = NULL;
    node->right = NULL;
    node->val = 0;
    node->is_end_node = '0';
}