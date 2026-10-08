#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    struct Node* left;
    struct Node* right;
}Node;

typedef struct Pair{
    //this container holds the two root 
    // pointers for the two trees 
    struct Node* small; // <=k
    struct Node* large; // >k
}Pair;

Pair* createPair(){
    Pair* pair = (Pair*) malloc(sizeof(Pair));
    pair->small = NULL;
    pair->large = NULL;

    return pair;
}

Node* createNode(int data){
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return node;
}

Node* insert(Node* root,int key){
    if(root == NULL)    return createNode(key);

    if(key<=root->data) root->left = insert(root->left,key);
    else    root->right = insert(root->right,key);

    return root ;
}

void inorder(Node* root){
    if(root == NULL)    return ;

    inorder(root->left);
    printf("%d ",root->data);
    inorder(root->right);
}

Pair* split(Node* root ,int key){
    if(root ==NULL) return createPair();

    if(key >= root->data){
        Pair * res = split(root->right,key);
        root->right = res->small;
        res->small = root ;
        return res;
    }

    else{
        Pair* res = split(root->left,key);
        root->left = res->large;
        res->large= root;
        return res;
    }
}

int main(){

    int arr[] = {50,30,70,20,40,60,80,45,65};
    int n = sizeof(arr)/sizeof(arr[0]);

    Node* root = NULL;

    for(int i= 0;i<n;i++){
        root = insert(root,arr[i]);
    }
    inorder(root);
    printf("\n");

    Pair* ans  = split(root,60);

    inorder(ans->small);
    printf("\n");
    inorder(ans->large);
    printf("\n");

}