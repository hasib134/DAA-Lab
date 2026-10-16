#include<stdio.h>
#include<stdlib.h>

#define alphabet_size 26

typedef struct Node{
    struct Node* ptr[alphabet_size];
    char end_node;
}Node;

typedef struct Trie{
    struct Node* root;
    int num_keys;
}Trie;

Node* createNode(){
    Node* node = (Node*)malloc(sizeof(Node));
    node->end_node = '0';

    for(int i=0;i<alphabet_size;i++){
        node->ptr[i] = NULL;
    }
    return node;
}

Trie * createTrie(){
    Trie * trie = (Trie*)malloc(sizeof(Trie));
    trie->root = createNode();
    trie->num_keys = 0;

    return trie;
}


void insert(Trie* trie,char * str){

    if(trie == NULL || str ==NULL)  return;

    Node* curr = trie->root;
    for(int i=0;str[i]!='\0';i++){
        int index = str[i]='a';
        if(index<0 || index>=alphabet_size) return ;

        if(curr->ptr[index]!='0'){
            curr->ptr[index] = createNode();
        }
        curr = curr->ptr[index];
    }
    if(curr->end_node =='0'){
        //if its is not the end node , then make it end node
        curr->end_node = '1';
        trie->num_keys++;
    }
    return curr;

}

//fuction checks whether a node have children or not
int check_child(Trie* tree,Node* node){
    for(int i=0;i<alphabet_size;i++){
        if(node->ptr[i]!=NULL){
            return 1 ;
        }
    }
    return 0;
}

Node* delete_helper(Node* curr,char * key,int depth,int* deleted){
    
}

int delete(Trie* trie,char* str){
    //recursive implementation 


}

int main(){

}