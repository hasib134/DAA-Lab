#include<stdio.h>
#include<stdlib.h>

#define alphabet 26
typedef struct Node{
    struct Node* ptr[alphabet];
    char end_Node;
}Node;

typedef struct Trie{
    struct Node* root;
    int size; // No of keys stored in the trie
}Trie;

// Initializing trie 

Node* createNode(){
    Node* node = (Node*)malloc(sizeof(Node));
    node->end_Node = '0';
    for(int i=0;i<alphabet;i++){
        node->ptr[i] = NULL;
    }
    return node;
}

Trie* createTrie(){
    Trie * trie = (Trie*)malloc(sizeof(Trie));
    trie->root = createNode();
    trie->size = '0';
    return trie;
}

void insert_in_Trie(Trie* trie,char *key){
    if(trie == NULL || key == NULL) return ;

    Node* curr = trie->root;
    for(int i=0;key[i]!='\0';i++){
        int index = key[i]-'a';
        //out of bound index
        if(index<0 || index>=alphabet){
            return ;
        }

        // if node is not present on that index
        if(curr->ptr[index] == NULL){
            curr->ptr[index] = createNode();

        }
        curr = curr->ptr[index];
    }


    if(curr->end_Node !='1'){
        curr->end_Node ='1';
        trie->size++;
    }

}

int search(Trie* trie,char* key){
    if(trie==NULL||trie->root==NULL || key == NULL)   return -1;

    Node* curr = trie->root;
    for(int i=0;key[i]!='\0';i++){
        int index = key[i] - 'a';
        
        if(index<0 || index>=alphabet){
            return -1;
        }
        if(curr->ptr[index]== NULL){
            return -1;
        }

        curr = curr->ptr[index];
    }

    return (curr !=NULL && curr->end_Node ==1);
}

int prefix_check(Trie* trie, char* str){
    if(trie == NULL ||trie->root ==NULL|| str == NULL) return -1;

    Node* curr = trie->root;
    for(int i=0;str[i]!='\0';i++){
        int index = str[i]-'a';

        if(index<0 || index>=alphabet){
            return -1;
        }

        if(curr->ptr[index]==NULL){
            return -1;
        }
        curr = curr->ptr[index];
    }
    //there exists a path 
    return 1;
}

int main(){

}