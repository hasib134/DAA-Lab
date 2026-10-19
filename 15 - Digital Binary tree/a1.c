#include<stdio.h>
#include<stdlib.h>

#define max_bit 12

typedef struct Node{
    struct Node* left;
    struct Node* right;
    char is_end_node; 
    int val;
}Node;

Node* createNode(){
    Node* node = (Node*)malloc(sizeof(Node));
    node->left =NULL;
    node->right = NULL;
    node->is_end_node = '0';
    node->val = 0;
    return node;
}

Node* insert(Node* root,int key){
    Node* curr = root;
    for(int i=max_bit-1;i>=0;i--){
        int bit =(key>>i) & 1;
        if(bit ==0){
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
    curr->is_end_node = '1';
    curr->val = key;
}

int search(Node* root,int key){
    Node* curr = root;
    
    for(int i= max_bit-1;i>=0;i--){
        if(curr == NULL)    return 0;
        int bit = (key>>i) & 1;

        if(bit == 0){
            curr = curr->left;
        }
        else{
            curr = curr->right;
        }
    }

    if(curr!=NULL && curr->is_end_node =='1')   return 1;
    return 0;
}

int main(){
    
}