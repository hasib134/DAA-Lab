#include<stdio.h>
#include<stdlib.h>

#define PRIME_P 10007
#define M_SLOTS 11
 
//universal hashing 

typedef struct Node{
    int key;
    char* plate;
    char* model;
    char* owner;
    struct Node* prev;
    struct Node* next;
}Node;

typedef struct HashTable{
    int m; // table capacity
    int p; // large prime number
    int a; // belongs to {1,2,3...p-1}
    int b; // belongs to {0,1,2...p-1}
    Node** table; // array of m node pointers 
    // h(a,b) = ((k*a + b) mod p)mod m;
}UHTable;

UHTable* createUHTable(int p,int m){
    UHTable* table = (UHTable*)malloc(sizeof(UHTable));
    table->m = m;
    table->p = p;

    table->a = 1 + rand()%(p-1); //taking a to be random value
    table->b = rand()%(p-1); // taking b to be random value
    
    table->table = (Node**)malloc(m*sizeof(Node*));

    return table;
}

Node* createCar(int key,char* plate,char* model,char* owner){
    Node* node = (Node*)malloc(sizeof(Node));
    node->key  = key;
    node->model = model;
    node->plate  =plate;
    node->owner = owner;
    
    node->next =NULL;
    node->prev = NULL;
    
    return node;
}

int hashFunction(UHTable* table , int k){
    long long x = k*table->a + table->b;
    int y = x % table->p;
    int hash_val = (y)%table->m;
    return hash_val;
}

//for collision resolution we are using seperate chaining 

void insert(UHTable* table,Node* car){
    int hash_key = hashFunction(table,car->key);
    car->next = table->table[hash_key];
    if(table->table[hash_key]!=NULL){
        table->table[hash_key]->prev = car;
    }
    table->table[hash_key] = car;
}

Node* search(UHTable* table,int key){
    int hash_key = hashFunction(table,key);
    Node* curr = table->table[hash_key];
    while(curr!=NULL){
        if(curr->key == key){
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

void printTable(UHTable* table){
    for(int i=0;i<table->m;i++){
        Node* curr = table->table[i];
        while(curr!=NULL){
            printf(" %d %s %s %s ",curr->key,curr->plate,curr->owner,curr->model);
            curr = curr->next;
        }
        printf("\n");

    }
}

int main(){
    UHTable* table =createUHTable(PRIME_P,M_SLOTS);
    Node *c1 = createCar(1100, "AS-01-AA-1100", "Honda City", "Rahul");
    Node *c2 = createCar(2200, "AS-01-BB-2200", "Hyundai Creta", "Priya");
    Node *c3 = createCar(3300, "AS-01-CC-3300", "Tata Nexon", "Aman");
    Node *c4 = createCar(4400, "AS-01-DD-4400", "Maruti Swift", "Sneha");
    Node *c5 = createCar(5500, "AS-01-EE-5500", "Mahindra XUV", "Vikram");

    insert(table,c1);
    insert(table,c2);
    insert(table,c3);
    insert(table,c4);
    insert(table,c5);

    printTable(table);

    Node* curr = search(table,4400);
    printf(" %d %s %s %s ",curr->key,curr->plate,curr->owner,curr->model);


}





