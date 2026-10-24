#include<stdio.h>
#include<stdlib.h>

// universal hashing 
typedef struct Node{
    int key;
    void * data;
    struct Node* next;
    struct Node* prev;
}Node;

typedef struct UHTable{
    int m;
    int p;
    int a;
    int b;
    Node ** table;
}UHTable;

Node* createNode(int key){
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->next =NULL;
    node->prev = NULL;
    node->data = NULL;
    return node;
}

UHTable* createTable(int p ,int m){
    UHTable* table = (UHTable*)malloc(sizeof(UHTable));
    table->m = m;
    table->p = p;
    
    table->a = 1 + rand() % p;
    table->b = rand() % p;

    table->table = (Node**)malloc(m * sizeof(Node*));
    for(int i=0;i<m;i++){
        table->table[i] = NULL;
    }

    return table;
}

int hashFunction(UHTable* table,int key){
    long long x = table->a * key + table->b;
    int y = x% table->p;
    int hash_value = y % table->m;
    return hash_value;
}

void insert(UHTable* table,Node* node){
    int slot = hashFunction(table,node->key);

    node->next = table->table[slot];
    if(table->table[slot]!=NULL){
        table->table[slot]->prev = node;
    }
    table->table[slot] = node;
}

void printTable(UHTable* table){
    for(int i=0;i<table->m;i++){
        Node* curr = table->table[i];
        while(curr!=NULL){
            printf("%d ",curr->key);
            curr = curr->next;
        }
        printf("\n");
    }
}


int main(){
    UHTable* ht = createTable(1009, 11);

    Node* n1 = createNode(10);
    Node* n2 = createNode(25);
    Node* n3 = createNode(3);
    Node* n4 = createNode(18);
    Node* n5 = createNode(29);
    Node* n6 = createNode(13);
    Node* n7 = createNode(45);
    Node* n8 = createNode(100);
    Node* n9 = createNode(231);
    Node* n10 = createNode(165);
    
    
    insert(ht, n1);
    insert(ht, n2);
    insert(ht, n3);
    insert(ht, n4);
    insert(ht, n5);
    insert(ht, n6);
    insert(ht, n7);
    insert(ht, n8);
    insert(ht, n9);
    insert(ht, n10);

    printTable(ht);

    return 0;
}