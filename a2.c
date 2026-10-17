#include<stdio.h>
#include<stdlib.h>

typedef struct Vector{
    int * data;
    int size;
    int capacity;
}Vector;

void initializeVector(Vector* vec){
    vec->size = 0;
    vec->capacity =2;
    vec->data = (int*)malloc(vec->capacity*sizeof(int));
}

void push_vector(Vector* vec,int val){
    if(vec->size == vec->capacity){
        vec->capacity *=2;
        vec->data = (int*)realloc(vec->data , vec->capacity*sizeof(int));
    }
    vec->data[vec->size] = val;
    vec->size++;
}

typedef struct Graph{
    Vector* adj; // array of struct vectors
    int n;
}Graph;

Graph* createGraph(int n){
    Graph* graph =(Graph*)malloc(sizeof(Graph));
    graph->n = n;
    graph->adj = (Vector*)malloc(n * sizeof(Vector));
    
    for(int i=0;i<n;i++){
        initializeVector(&graph->adj[i]);
    }
    return graph;
}

void addEdge(Graph* graph,int u,int v){
    push_vector(&graph->adj[u],v);
    push_vector(&graph->adj[v],u);
}

void printGraph(Graph* graph){
    for(int i = 0;i<graph->n;i++){
        for(int j=0;j<graph->adj[i].size;j++){
            printf("%d\t",graph->adj[i].data[j]);
        }
        printf("\n");
    }
}

int main(){
    int n =5 ;
    Graph* graph = createGraph(n);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);
    printGraph(graph);
}