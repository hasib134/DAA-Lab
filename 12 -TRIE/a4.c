#include<stdio.h>
#include<stdlib.h>

#define size 26

typedef struct Node{
    struct Node* ptr[size];
    char is_end_Node;
}Node;

typedef struct Trie{
    Node* root;
    int keys;
}Trie;

Node* createNode(){
    Node* node = (Node*)malloc(sizeof(Node));
    for(int i=0;i<size;i++){
        node->ptr[i] = NULL;
    }
    node->is_end_Node ='0';
    return node;
}

Node* createTrie(){
    Trie * tree = (Trie*)malloc(sizeof(Trie));
    tree->root = createNode();
    tree->keys = 0;
    return tree;
}

void insertInTrie(Trie* tree,char* str){
    if(tree == NULL || str == NULL || tree->root==NULL) return;
    Node* curr = tree->root;
    for(int i=0;str[i]!='\n';i++){
        int index = str[i]-'a';

        if(index<0 || index>=size)   return ;

        if(curr->ptr[index] == NULL){
            curr->ptr[index] == createNode();
        }
        curr = curr->ptr[index];
    }

    if(curr->is_end_Node!='1'){
        curr->is_end_Node = '1';
        tree->keys ++;
    }
}   

int check_NULL_Node(Node* node){
    for(int i=0;i<size;i++){
        if(node->ptr[i]!=NULL){
            return 0;
        }
    }
    return 1;
}

Node* deleteKey(Node* root,char * str,char *success,int depth){
    //depth keeps the track of index where we are at curr str
    if(root == NULL)    return ;

    //if you are at end of the string 
    if(str[depth] =='\0'){

        //if root is the end node
        if(root->is_end_Node=='1'){
            root->is_end_Node='0';
            success = '1';
        }

        // node is not the end node
        if(check_NULL_Node(root)==1){
            free(root);
            root = NULL;
        }
        return ;
    }

    int index = str[depth]-'a';

    if(index<0 || index>=size)  return root;

    root->ptr[index] = deleteKey(root->ptr[index],str,success,depth+1);


    if(check_NULL_Node(root) == '1' && root->is_end_Node=='0'){
        free(root);
        root = NULL;
    }
    return root;
}

char deleteInTrie(Trie* trie,char * str){
    if(trie == NULL || trie->root ==NULL || str==NULL)  return '0';

    char success = '0';
    trie->root = deletekey(trie->root,str,&success,0);


}


int main(){

}