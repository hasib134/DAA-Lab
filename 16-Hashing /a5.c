#include<stdio.h>
#include<stdlib.h>

#define m_slots 23
#define prime_p 10007

//Open Addressing using random hash function

typedef struct Node{
    int key;
    void * data;
    char state;
}Node;

typedef struct HashTable{
    int m;
    int p;
    int a;
    int b;
    Node** table;
}HashTable;

Node* createnode(int key){
    Node* node =(Node*)malloc(sizeof(Node));
    node->key = key;
    node->data =NULL;
    node->state = '0';
    return node;
}

HashTable* createHTable(int p ,int m){
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    table->p = p;
    table->m = m;

    table->a = 1 + rand()%(p-1);
    table->b = rand()%p;

    table->table = (Node**)malloc(m * sizeof(Node*));
    for(int i=0;i<m;i++){
        table->table[i] = (Node*)malloc(sizeof(Node));
        table->table[i]->state = '0';
    }
    return table;
}

int hashFunction(HashTable* table,int i ,int key){
    //h(k,i) = (h1(k)+ i)mod m;
    // h1 = ((a*key + b )%p)%m;

    long long x = table->a*key + table->b;
    int y = x % table->p;
    int hash_val = y% table->m;
    return (hash_val + i)%table->m;
}

void insert(HashTable* table,Node* node){
    int success=0;
    for(int i=0;i<table->m;i++){
        int slot = hashFunction(table,i,node->key);
        if(table->table[slot]->state =='0' || table->table[slot]->state =='2'){
            table->table[slot] = node;
            table->table[slot]->state = '1';
            success =1;
            break;
        }
    }
    if(success){
        printf("Inserted Successfully\n");
    }
    else{
        printf("Table is full\n");
    }
}

Node* search(HashTable* table,int key){
    for(int i=0;i<table->m;i++){
        int slot = hashFunction(table,i,key);
        if(table->table[slot]->key == key && table->table[slot]->state=='1'){
            return table->table[slot];
        }
    }
    return NULL;

}

void printTable(HashTable* table){
    for(int i =0l;i<table->m;i++){
        printf("%d\n",table->table[i]->key);
    }
}
int main(){
    HashTable* table = createHTable(prime_p,m_slots);
    Node* n1 = createnode(23);
    Node* n2 = createnode(19);
    Node* n3 = createnode(45);
    Node* n4 = createnode(89);
    Node* n5 = createnode(910);
    Node* n6 = createnode(345);
    Node* n7 = createnode(276);
    Node* n8 = createnode(69);
    Node* n9 = createnode(85);
    Node* n10 = createnode(77);
    Node* n11 = createnode(88);

    //from here table will be full 
    Node* n12 = createnode(145);
    Node* n13 = createnode(98);
    Node* n14 = createnode(100);

    insert(table,n1);
    insert(table,n2);
    insert(table,n3);
    insert(table,n4);
    insert(table,n5);
    insert(table,n6);
    insert(table,n7);
    insert(table,n8);
    insert(table,n9);
    insert(table,n10);
    insert(table,n11);
    insert(table,n12);
    insert(table,n13);
    insert(table,n14);
    // insert(table,n15);
    printTable(table);

    Node* curr = search(table,45);
    printf("%d\n",curr->key);
}