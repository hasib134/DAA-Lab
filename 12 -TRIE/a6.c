#include<stdio.h>
#include<stdlib.h>

#define size 26

typedef struct Node{
    struct Node* ptr[size];
    char is_end_node;
}Node;

typedef struct Trie{
    Node* root ;
    int no_keys;
}Trie;

Node* createNode(){
    Node* node = (Node*)malloc(sizeof(Node));
    node->is_end_node = '0';
    for(int i=0;i<size;i++){
        node->ptr[i] = NULL;
    }
    return node;
}

Trie* createTrie(){
    Trie* trie = (Trie*)malloc(sizeof(Trie));
    trie->root = createNode();
    trie->no_keys = 0;
    return trie;
}

void insert(Trie* trie,char* str){
    if(trie == NULL || trie->root == NULL || str == NULL)   return ;

    Node* curr = trie->root;
    for(int i =0;str[i]!='\0';i++){
        int index = str[i]-'a';

        if(index<0 || index>=size)  return ;

        if(curr->ptr[index]==NULL){
            curr->ptr[index] = createNode();
        }
        curr = curr->ptr[index];
    }
    if(curr->is_end_node!='1'){
        curr->is_end_node='1';
        trie->no_keys ++;
    }
}


int check_NULL(Node* root){
    Node* curr = root;
    for(int i=0;i<size;i++){
        if(curr->ptr[i]!=NULL){
            return 0;
        }
    }
    return 1;
}

Node* deleteKeyInTrie(Node* root , char* str, int *success,int depth){
    if(root == NULL)    return root;

    if(str[depth]=='\0'){

        if(root->is_end_node == '1'){
            root->is_end_node='0';
            *success = 1;
        }

        if(check_NULL(root)==1){
            free(root);
            root = NULL;
        }
        return root;
    }

    int index = str[depth]-'a';

    if(index<0 || index>=size)  return root;

    root->ptr[index] = deleteKeyInTrie(root->ptr[index],str,success,depth+1);

    if(root->is_end_node == '0' && check_NULL(root)){
        free(root);
        root = NULL;
    }
    return root;
}




int deleteKeys(Trie* trie, char * str){
    if(trie == NULL || trie->root == NULL || str ==NULL)    return 0;

    int success = 0;
    int depth = 0;
    trie->root = deleteKeyInTrie(trie->root,str,&success,depth);

    if(success == 1){
        trie->no_keys  --;
    }
    return success;

}

void printKeysDFS(Node* root, char buffer[],int depth){
    if(root ==NULL) return;

    if(root->is_end_node=='1'){
        buffer[depth] = '\0';
        printf("%s ",buffer);
    }

    for(int i=0;i<size;i++){
        if(root->ptr[i]!=NULL){
            buffer[depth] = (char)(i+'a');
            printKeysDFS(root->ptr[i],buffer,depth+1);
        }
    }

}

void printKeys(Trie* trie){
    if(trie ==NULL || trie->root == NULL)   return ;
    char buffer[100];

    printKeysDFS(trie->root,buffer,0);

}

int search(Trie* trie , char * str){
    if(trie == NULL | trie->root ==NULL || str == NULL) return 0;
    Node* curr = trie->root;

    for(int i=0;i<str[i]!='\0';i++){
        int index = str[i]-'a';

        if(index<0 || index >=size) return 0;

        if(curr->ptr[index]==NULL){
            return 0;
        }
        curr = curr->ptr[index];
    }

    if(curr->is_end_node=='1'){
        return 1;
    }
    return 0;
}

int main(){

    Trie* trie = createTrie();

    // Insert out of order
    insert(trie, "zebra");
    insert(trie, "apple");
    insert(trie, "application");
    insert(trie, "apply");
    insert(trie, "bat");
    insert(trie, "ball");

    printKeys(trie);
    printf("\n");

    deleteKeys(trie,"apple");
    printKeys(trie);
    printf("\n");
    
}