#include<stdio.h>
#include<stdlib.h>

#define max_bits 31 

typedef struct Node{
    struct Node* left;
    struct Node* right;
    char is_end_node;
    int value;
}Node;

typedef struct Trie{
    Node* root;
    int no_keys;
}Trie;

Node* createNode(){
    Node* node = (Node*)malloc(sizeof(Node));
    node->left =NULL;
    node->right = NULL;
    node->is_end_node ='0';
    node->value = 0;
    return node;
}

Trie* createTrie(){
    Trie* trie = (Trie*)malloc(sizeof(Trie));
    trie->no_keys = 0;
    trie->root  = createNode();

    return trie;
}

void insert(Trie* trie, int key){
    if(trie == NULL || trie->root == NULL)  return ;

    Node* curr = trie->root;
    for(int i = max_bits-1;i>=0;i--){
        int bit = (key>>i)&1;

        if(bit == 0 ){
            if(curr->left==NULL){
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
    if(curr->is_end_node != '1'){
        curr->is_end_node = 1;
        trie->no_keys ++;
        curr->value = key;
    }
}

int check_NULL(Node* node){
    if(node->left==NULL && node->right==NULL)   return 1;
    return 0 ; 
}
Node* deleteKey(Node* root, int key,int *success,int bit_index){
    if(root == NULL)    return NULL;
    if(bit_index<0){
        if(root->is_end_node=='1'){
            root->is_end_node = '0';
            *success = 1;
        }

        if(check_NULL(root)){
            free(root);
            return NULL;
        }
    }

    int bit = (key >> bit_index)&1;
    if(bit == 0){
        root->left = deleteKey(root->left,key,success,bit_index-1);
    }
    else{
        root->right = deleteKey(root->right,key,success,bit_index-1);
    }

    if(check_NULL(root) && root->is_end_node=='0'){
        free(root);
        return NULL;
    }
    return root;
}


int deleteInTrie(Trie* trie,int key){
    if(trie == NULL || trie->root == NULL)  return 0 ;

    int success = 0;
    int bit = (key>>(max_bits-1)) & 1;
    trie->root = deleteKey(trie->root,key,&success,max_bits-1);

    if(success){
        trie->no_keys --;
    }
    return success;
}

void printKeysDFS(Node* root){
    if(root ==NULL) return ;

    if(root->is_end_node ==1){
        printf("%d ",root->value);
    }
    printKeysDFS(root->left);
    printKeysDFS(root->right);
}

void printkeys(Trie* trie){
    if(trie ==NULL || trie->root==NULL) return ;

    printKeysDFS(trie->root);
}

int main(){

    Trie* trie = createTrie();
    int arr[]= {1,5,3,10,43,23,67,12};
    int n = sizeof(arr)/sizeof(arr[0]);

    for(int i=0;i<n;i++){
        insert(trie,arr[i]);
    }
    printkeys(trie);
    printf("\n");

    deleteInTrie(trie,10);
    printkeys(trie);

}