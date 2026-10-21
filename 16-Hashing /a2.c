#include<stdio.h>
#include<stdlib.h>

//Seperate chaining 
typedef struct Node{
    int key;
    struct Node* next;
    struct Node* prev;
}Node;

typedef struct HashTable{
    int m ;
    Node **table; // t[0,1,...m-1]
}HashTable;

Node* createNode(int key){
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->next = NULL;
    node->prev  = NULL;
    return node;
}

//here we are usinh hash function : h(k) = k % m 

int hash_function(HashTable* table,int key){
    int rem = key % table->m;

    if(rem<0){
        rem = rem + table->m;
    }
    return rem;
}

HashTable* createHashTable(int m){
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    table->m = m;
    table->table = (Node**)calloc(m,sizeof(Node*));
    return table;
}
void insert(HashTable* table , Node* node ){
    int index = hash_function(table,node->key);
    node->next = table->table[index];
    if(table->table[index]!=NULL){
        table->table[index]->prev = node;
    }
    table->table[index] = node;
    node->prev = NULL;
}

Node* search(HashTable* table , int key){
    int index = hash_function(table , key);

    Node* temp = table->table[index];
    while(temp!=NULL && temp->key!=key){
        temp = temp->next;
    }
    return temp;
}

void delete(HashTable* table, int key){
    int index = hash_function(table,key);

    Node* temp = table->table[index];
    while(temp!=NULL && key != temp->key){
        temp = temp->next;
    }
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    free(temp);
}


int main(){

}