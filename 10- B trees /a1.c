#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct BTreeNode{
    int *keys; //aray of keys
    int n; // no of keys in the node
    bool leaf;  // is node a leaf 
    struct BTreeNode **children; // array of children pointers
}BTreeNode;

typedef struct Btree{
    BTreeNode * root; //ponter to the root 
    int t; //minimum degree of the B tree 
}BTree;





int main(){

}