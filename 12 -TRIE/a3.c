#include<stdio.h>
#include<stdlib.h>

#define alphabet_size 26

typedef struct Node{
    struct Node* ptr[alphabet_size];
    char is_endNode;
}Node;

typedef struct Trie{
    Node* root;
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
    trie->num_keys=0;
    return trie;
}

void insert(Trie* trie,char* key){
    if(trie == NULL || trie->root == NULL || key==NULL) return ;
    Node* curr = trie->root;

    for(int i=0;key[i]!='\0';i++){
        int index = key[i]-'a';
        if(index< 0 || index >= alphabet_size) return;

        if(curr->ptr[index]==NULL){
            curr->ptr[index] = createNode();
        }
        curr = curr->ptr[index];
    }
    if(curr->is_endNode=='0'){
        curr->is_endNode='1';
        trie->num_keys++;
    }

}

int check_node_IsNull(Node* node){
    for(int i=0;i<alphabet_size;i++){
        if(node->ptr[i]!=NULL){
            return 0;
        }
    }
    return 1;
}

Node* delete(Node* curr , char* key,int depth,int* success){
    if(curr ==NULL) return NULL;

    if(key[depth]=='\0'){
        //you are at the last node
        //check if it is a end node
        if(curr->is_endNode =='1'){
            curr->is_endNode='0';
            *success = 1;
        }

        //if it is not end node, and a useless node
        if(check_node_IsNull(curr)==1){
            free(curr);
            curr = NULL;
        } 
        return curr;
    }

    // if it is not the end node 
    int index = key[depth]-'a';
    if(index<0 | index>=alphabet_size)  return curr;

    // recursively delete the node
    curr->ptr[index] = delete(curr->ptr[index],key,depth+1,success);

    if(check_node_IsNull(curr) && curr->is_endNode=='0'){
        free(curr);
        curr = NULL;
    }
    return curr;
}

int delete_key(Trie* trie,char* key){
    if(trie==NULL || trie->root ==NULL || key ==NULL)   return 0;
    
    int success = 0;
    trie->root = delete(trie->root,key,0,&success);

    if(success ==1){
        trie->num_keys -- ;
    }
    return success;
}

void print_keys_dfs(Node* curr, char word[],int depth){
    if(curr == NULL)    return;

    if(curr->is_endNode =='1'){
        word[depth] = '\0';
        printf("%s\n",word);
    }

    for(int i = 0;i<alphabet_size;i++){
        if(curr->ptr[i]!=NULL){
            word[depth] = (char)('a'+i);
            print_keys_dfs(curr->ptr[i],word,depth+1);
        }
    }
}

void print_all_keys(Trie* trie){
    if(trie == NULL || trie->num_keys ==0 || trie->root ==NULL){
        printf("trie is empty\n");
        return;
    }
    //character buffer of max length 
    char word[100];
    print_keys_dfs(trie->root,word,0); 

}


int main() {
    Trie* trie = createTrie();

    // Insert out of order
    insert(trie, "zebra");
    insert(trie, "apple");
    insert(trie, "application");
    insert(trie, "apply");
    insert(trie, "bat");
    insert(trie, "ball");

    print_all_keys(trie);
}
