#include<stdio.h>
#include<stdlib.h>

//Direct Address table 

#define U_size 1000 //{0,1,...999}
typedef struct Node{
    int key;
    char* plate;
    char* model;
    char* owner;
}Node;

typedef struct DirectAddressTable{
    Node* table[U_size];
} DirectAddressTable;

void initializeTable(DirectAddressTable* DTable){
    for(int i=0;i<U_size;i++){
        DTable->table[i] = NULL;
    }
}

Node* createNewCar(int key,char* plate,char* model,char* owner){
    Node* car  = (Node*)malloc(sizeof(Node));
    car->key = key;
    car->plate = plate;
    car->model = model;
    car->owner= owner;

    return car;
}

void insert(DirectAddressTable* DTable ,Node* car){
    if(car == NULL || car->key< 0 || car->key>=U_size){
        return ;
    }
    DTable->table[car->key] = car;
}

Node* search(DirectAddressTable* DTable,int key){
    if(key<0 || key>=U_size)    return NULL;
    return DTable->table[key];
}

void delete(DirectAddressTable* Dtable , Node* car){
    if(car == NULL || car->key<0 || car->key >=U_size)  return ;
    
    Node* temp = Dtable->table[car->key];
    Dtable->table[car->key] = NULL;
    free(temp);
}

int main(){

}