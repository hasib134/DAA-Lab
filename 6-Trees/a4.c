#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    struct node* left;
    struct node* right;
};

struct node* createNode(int data){
    struct node* x = (struct node*)malloc(sizeof(struct node));

    x->data = data;
    x->left = NULL;
    x->right = NULL;

    return x ; 
}

struct node* createtree(int arr[],int i,int n ){
    if(i>=n)    return NULL;

    struct node* root = createNode(arr[i]);
    root->left = createtree(arr,2*i+1,n);
    root->right = createtree(arr,2*i+2,n);

    return root;
}

void inorder(struct node* root){
    if(root == NULL)    return ;

    inorder(root->left);
    printf("%d ",root->data);
    inorder(root->right);
}
int main(){
    // creating tree from array 

    int arr[]= {1,2,3,4,5,6,7,8,9,10};
    int n = sizeof(arr)/sizeof(arr[0]);

    struct node* root = createtree(arr,0,n);

    inorder(root);


}