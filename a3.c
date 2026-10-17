#include<stdio.h>
#include<stdlib.h>

typedef struct Vector{
    int* data;
    int size;
    int capacity;
}Vector;

void initializeVector(Vector* vec){
    vec->size = 0;
    vec->capacity = 2;
    vec->data = (int*)malloc(vec->capacity*sizeof(int));
}

void push_val(Vector* vec,int val){
    if(vec->size == vec->capacity){
        vec->capacity *=2;
        vec->data = (int*)realloc(vec->data,vec->capacity*sizeof(int));
    }
    vec->data[vec->size] = val;
    vec->size++;    
}

typedef struct Graph{
    int n;
    Vector* adj; // array of vector
}Graph;

Graph* initilizeGraph(int n){
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->n = n;
    graph->adj = (Vector*)malloc(n*sizeof(Vector));

    for(int i=0;i<n;i++){
        initializeVector(&graph->adj[i]);
    }
    return graph;
}

void add_edge(Graph* graph,int u,int v){
    push_val(&graph->adj[u],v);
    push_val(&graph->adj[v],u);
}

void DFS_recursive(Graph* graph, int node,int* visited){
    visited[node] = 1;
    printf("%d ",node);
    for(int i=0;i<graph->adj[i].size;i++){
        if(!visited[graph->adj->data[i]]){
            DFS_recursive(graph, graph->adj->data[i],visited);
        }
    }
}

void DFS(Graph* graph){
    int n = graph->n;
    int visted[n];
    for(int i=0;i<n;i++)    visted[i]=0;

    for(int i=0;i<n;i++){
        if(!visted[i])  DFS_recursive(graph,i,visted);
    }
}


int main(){
    int vertices = 6;
    Graph *graph = initilizeGraph(vertices);

    add_edge(graph, 0, 1);
    add_edge(graph, 0, 2);
    add_edge(graph, 1, 3);
    add_edge(graph, 1, 4);
    add_edge(graph, 2, 4);
    add_edge(graph, 3, 5);
    add_edge(graph, 4, 5);

    DFS(graph);
}