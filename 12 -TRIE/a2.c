#include<stdio.h>
#include<stdlib.h>

#define alphabet_size 26

typedef struct Node{
    struct Node* ptr[26];
    char is_endNode;
}Node;

typedef struct Trie{
    struct Node* root;
    int num_keys;
}Trie;

Node* createNode(){
    Node* node = (Node*)malloc(sizeof(Node));
    node->is_endNode = '0';
    for(int i=0;i<alphabet_size;i++){
        node->ptr[i] = NULL;
    }
    return node;
}

Trie* createTrie(){
    Trie* trie = (Trie*)malloc(sizeof(Trie));
    trie->root = createNode();
    trie->num_keys = 0;

    return trie;
}

void insert(Trie* trie,char* key){
    if(trie == NULL || trie->root == NULL|| key == NULL)    return ;

    Node* curr = trie->root;
    for(int i=0;key[i]!='\0';i++){
        int index = key[i] -'a';

        if(index < 0 || index >= alphabet_size){
            return ;
        }
        
        if(curr->ptr[index]!=NULL){
            curr->ptr[index] = createNode();
        }
        curr = curr->ptr[index];
    }
    if(curr->is_endNode == '0'){
        curr->is_endNode ='1';
        trie->num_keys++;
    }
}

//check if node contains any null pointers 
char check_NULL_node(Node* node){
    for(int i=0;i<alphabet_size;i++){
        if(node->ptr[i]!=NULL){
            return '1';
        }
    }
    return '0';
}

Node* delete(Node* root, char* key,char *success,int depth){
    if(root == NULL){
        return NULL;
    }

    //depth keep track of index of char in the str that we are currently on 
    if(key[depth] == '\0'){
        //you are at the last node
        //check if the node is end node or not 
        if(root->is_endNode =='1'){
            root->is_endNode = '0';
            success = '1';
        }
        
        //node is not an end node and check if it. has any pointer or not
        if(check_NULL_node(root) == '0'){
            free(root);
            root = NULL;
        }
        return root;
    }
    //calculate the index of the node
    int index = key[depth]-'a';
    if(index<0 || index>=alphabet_size){
        return root;
    }
    //recursively do it
    root->ptr[index] = delete(root->ptr[index],key,success,depth+1);


    //now back track 
    //check if the root node has any child and it is not an end node
    //so it useless node
    if(check_NULL_node(root) == '0' && root->is_endNode =='0'){
        free(root);
        root = NULL;
    }
    return root;

}
char delete_key(Trie* trie,char* key){
    if(trie ==NULL || trie->root == NULL || key==NULL)  return '0';

    //check if a node is successfully deleted or not 
    char success = '0';

    trie->root = delete(trie->root,key,&success,0);

    if(success =='1'){
        trie->num_keys -- ;
    }
    return success;
}




int main(){

}