#include<stdio.h>
#include<stdlib.h>

#define max_bits 31

typedef struct Node{
    struct Node* left;
    struct Node* right;
    char is_end_Node;
    int value;
}Node;

typedef struct Trie{
    Node* root;
    int noKeys;
}Trie;

Node* createNode(){
    Node* node = (Node*)malloc(sizeof(Node));
    node->left = NULL;
    node->right = NULL;
    node->is_end_Node = '0';
    node->value = 0;
    return node;
}

Trie* createTrie(){
    Trie* trie = (Trie*)malloc(sizeof(Trie));
    trie->root = createNode();
    trie->noKeys =0;
    return trie;
}

void insert(Trie* trie , int key){
    if(trie == NULL || trie->root==NULL){
        return ;
    }
    Node* curr = trie->root;
    for(int i=max_bits-1;i>=0;i--){
        int bit  = (key>>i) & 1; 

        if(bit == 0){
            if(curr->left == NULL){
                curr->left = createNode();
            }
            curr = curr->left;
        }   
        else{
            if(curr->right==NULL){
                curr->right = createNode();
            }
            curr = curr->right;
        }
    }

    if(curr->is_end_Node!='1'){
        curr->is_end_Node='1';
        curr->value = key;
        trie->noKeys ++;
    }
}

void printKeysDFS(Node* root){
    if(root == NULL)    return ;

    if(root->is_end_Node=='1'){
        printf("%d ",root->value);
    }

    if(root->left!=NULL)    printKeysDFS(root->left);
    if(root->right!=NULL)   printKeysDFS(root->right);
}

void printkeys(Trie* trie){
    if(trie == NULL || trie->root == NULL)  return ;

    printKeysDFS(trie->root);
}

int main(){
    Trie* trie = createTrie();
    int arr[] = {58,24,69,100,128,12,45,1};
    int n = sizeof(arr)/sizeof(arr[0]);

    for(int i =0;i<n;i++){
        insert(trie,arr[i]);
    }

    printkeys(trie);
}
