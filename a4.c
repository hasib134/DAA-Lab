#include<stdio.h>
#include<stdlib.h>
#define max_vertices 100

typedef struct Vector{
    int* data;
    int size;
    int capacity;
}Vector;

void initializeVector(Vector* vec){
    vec->size = 0;
    vec->capacity = 2;
    vec->data = (int*)malloc(vec->capacity * sizeof(int));
}

void push_node(Vector* vec,int node){
    if(vec->size == vec->capacity){
        vec->capacity*=2;
        vec->data = (int*)realloc(vec->data,vec->capacity*sizeof(int));
    }
    vec->data[vec->size] = node;
    vec->size++;
}

typedef struct Graph{
    int n;
    Vector* adj; // array of nodes
}Graph;

Graph * initializeGraph(int n){
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->n = n;
    graph->adj = (Vector*)malloc(n*sizeof(Vector));

    for(int i=0;i<n;i++){
        initializeVector(&graph->adj[i]);
    }
    return graph;
}   

void add_edge(Graph* graph ,int u,int v){
    push_node(&graph->adj[u],v);
    push_node(&graph->adj[v],u);
}

typedef struct Queue{
    int elements[max_vertices];
    int front;
    int rear;

}Queue;

Queue* createQueue(){
    Queue * q =(Queue*)malloc(sizeof(Queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

int isempty(Queue* q){
    if(q->rear == -1)   return 1;

    return 0;
}

void enqueue(Queue* q, int ele){
    if(q->rear == max_vertices-1){
        //Queue is full
        return ;
    }
    if(q->front == -1){
        q->front = 0;
    }
    q->rear++;
    q->elements[q->rear] = ele;
}
int dequeue(Queue* q){
    if(q->rear ==-1){
        //queue is empty
        return -1;
    }
    int item = q->elements[q->front];
    q->front++;

    if(q->front>q->rear){
        q->front = -1;
        q->rear = -1;
    }
    return item;

}

void bfs(Graph* graph,int start_node){
    int * visited =(int*)calloc(graph->n ,sizeof(int));  
    Queue* queue = createQueue();
    enqueue(queue,start_node);
    visited[start_node] = 1;

    while(!isempty(queue)){
        int u = dequeue(queue);
        printf("%d ",u);

        for(int i=0;i<graph->adj[u].size;i++){
            int neig = graph->adj[u].data[i];
            if(!visited[neig]){
                visited[neig]=1;
                enqueue(queue,neig);
            }
        }
    }
}

int main(){
    int n = 6;
    Graph* graph = initializeGraph(n);
    add_edge(graph, 0, 1);
    add_edge(graph, 0, 2);
    add_edge(graph, 1, 3);
    add_edge(graph, 1, 4);
    add_edge(graph, 2, 5);
    add_edge(graph, 4, 5);

    bfs(graph, 0);

}