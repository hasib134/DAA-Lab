#include<stdio.h>
#include<stdlib.h>

#define m_slot 13
#define p_prime 10007

//double hashing

// state = 0 -> free slot
// state = 1 -> occupied slot
// state = 2 -> deleted slot

typedef struct Node{
    int key;
    void * data;
    char state;
}Node;

typedef struct HashTable{
    int m;
    int p;
    int a1,b1; // parameters for h1 
    int a2,b2; // parameters for h2 
    Node** table;
}HashTable;

Node* createNode(int key){
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->data = NULL;
    node->state = '0';
    return node;
}
HashTable* createTable(int p,int m){
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    table->m =m;
    table->p = p;
    table->a1 = 1 + rand()%(p-1); 
    table->a2 = 1 + rand()%(p-1); 

    table->b1 = rand()% p; 
    table->b2 = rand()% p; 

    table->table = (Node**)malloc(m*sizeof(Node*));
    for(int i=0;i<m;i++){
        table->table[i] = (Node*)malloc(sizeof(Node));
        table->table[i]->state = '0';
        table->table[i]->key = -1;
        table->table[i]->data = NULL;
    }

    return table;
} 

int hashFunction(HashTable* table , int i ,int key){
    //h1 = ((a1*k+b1)%p)m
    //h2 = ((a2*k+b2)%p)m
    
    // h(k,i) = (h1 + i*h2)%m
    
    long long x1 = table->a1*key + table->b1;
    int y1 = (int)(x1 % table->p);
    int z1 = (int)(y1 % (table->m));
    
    long long x2 = table->a2*key + table->b2;
    int y2 = (int)(x2%table->p);
    int z2 = 1+ (int )(y2% (table->m-1));


    int hash_val = (z1 + i*z2)%table->m;

    return hash_val;
}

void insert(HashTable* table,Node* node){
    for(int i=0;i<table->m;i++){
        int slot = hashFunction(table,i,node->key);
        if(table->table[slot]->state =='1' && table->table[slot]->key ==node->key){
            //key already exists 
            free(node);
            return ;
        }

        if(table->table[slot]->state =='0' || table->table[slot]->state =='2'){
            free(table->table[slot]);
            table->table[slot] = node;
            table->table[slot]->state = '1';
            printf("Inserted Successfully\n");
            return ;
        }
    }
    printf("Table is Full\n");
}

Node* search(HashTable* table,int key){
    for(int i=0;i<table->m;i++){
        int slot = hashFunction(table,i,key);

        if(table->table[slot]->state=='0'){
            //key dont exists 
            return NULL;
        }
        if(table->table[slot]->state=='1' && table->table[slot]->key == key){
            return table->table[slot];
        }
    }
    return NULL;
}

void printTable(HashTable* table){
    for(int i=0;i<table->m;i++){

        if(table->table[i]->state=='1'){
            printf("%d",table->table[i]->key);
        }
        printf("\n");
        
    }
}

int main(){
    HashTable* table = createTable(p_prime,m_slot);
    Node* n1 = createNode(100); 
    Node* n2 = createNode(23); 
    Node* n3 = createNode(45); 
    Node* n4 = createNode(69); 
    Node* n5 = createNode(19); 
    Node* n6 = createNode(2); 
    Node* n7 = createNode(13); 
    Node* n8 = createNode(79); 
    Node* n9 = createNode(86); 
    Node* n10 = createNode(1030); 
    Node* n11 = createNode(245); 
    Node* n12 = createNode(631); 
    Node* n13 = createNode(878); 
    Node* n14 = createNode(1987);
    Node* n15 = createNode(1653);
    Node* n16 = createNode(326);
    Node* n17 = createNode(8787);


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
    insert(table,n15);
    insert(table,n16);
    insert(table,n17);

    printTable(table);
}