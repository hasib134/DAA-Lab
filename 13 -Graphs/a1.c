#include<stdio.h>
#include<stdlib.h>

int main(){
    int n,m;
    printf("Enter no of nodes and edges\n");
    scanf("%d %d",&n,&m);
    int **adj = malloc(n*sizeof(int*));
    for(int i=0;i<n;i++){
        adj[i] =calloc(n,sizeof(int)); 
    }

    //for undirected graph
    for(int i=0;i<m;i++){
        int u,v;
        scanf("%d %d",&u,&v);
        adj[u][v] =1;
        adj[v][u] =1;
    }

    // for directed graph
        for(int i=0;i<m;i++){
        int u,v;
        scanf("%d %d",&u,&v);
        adj[u][v] =1;
    }

}