#include<stdio.h>
#include<stdlib.h>

#define size 26

typedef struct Node{
    struct Node* ptr[size];
    char is_end_node;
}Node;

typedef struct Trie{
    Node* root;
    int No_keys;
}Trie;

Node* createNode(){
    Node* node = (Node*)malloc(sizeof(Node));
    for(int i=0;i<size;i++){
        node->ptr[i] = NULL;
    }
    node->is_end_node='0';
    return node;
}

Trie* createTrie(){
    Trie* trie = (Trie*)malloc(sizeof(Trie));
    trie->root = createNode();
    trie->No_keys = 0;

    return trie;
}

void insert(Trie* trie,char * str){
    if(str == NULL || trie == NULL) return;

    Node* curr = trie->root;
    for(int i=0;str[i]!='\0';i++){
        int index = str[i]-'a';

        if(index<0 || index>=size)  return ;

        if(curr->ptr[index]==NULL){
            curr->ptr[index] = createNode();
        }
        curr = curr->ptr[index];
    }
    if(curr->is_end_node!='1'){
        curr->is_end_node = '1';
        trie->No_keys ++;
    }

}

int check_is_NULL(Node* root){
    for(int i=0;i<size;i++){
        if(root->ptr[i] !=NULL){
            return 0;
        }
    }
    return 1;
}

Node* deleteKey(Node* root , char * str,int *success,int depth){
    if(root == NULL) return NULL;

    if(str[depth]=='\0'){
        if(root->is_end_node == '1'){
            root->is_end_node ='0';
            *success = 1;
        }

        if(check_is_NULL(root) ==1){
            free(root);
            root = NULL;
        }
        return root;
    }

    int index = str[depth]-'a';

    if(index<0 || index>=size)  return root;

    root->ptr[index] = deleteKey(root->ptr[index],str,success,depth+1);

    if(check_is_NULL(root) == 1 && root->is_end_node =='0'){
        free(root);
        root = NULL;
    }
    return root;

}

int deleteInTrie(Trie* trie , char * str){
    if(str ==NULL || trie ==NULL || trie->root == NULL) return 0;

    int success = 0;

    trie->root = deleteKey(trie->root,str,&success,0);
    if(success){
        trie->No_keys--;
    }
    return success;
}

void printKeyDFS(Node* curr , char buffer[],int depth){
    if(curr == NULL)    return ;

    if(curr->is_end_node=='1'){
        buffer[depth] ='\0';
        printf("%s ",buffer);
    }

    for(int i=0;i<size;i++){
        if(curr->ptr[i]!=NULL){
            buffer[depth] = (char)('a'+i);
            printKeyDFS(curr->ptr[i],buffer,depth+1);
        }
    }
}

void printKey(Trie* trie){
    if(trie == NULL)    return ;

    char buffer[100];
    printKeyDFS(trie->root,buffer,0);
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

    printKey(trie);

}