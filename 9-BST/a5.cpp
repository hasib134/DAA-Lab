#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    int v;//stores no of nodes in the underlying structure;
    struct Node* left;
    struct Node* right;
}Node;

Node* createNode(int data){
    Node* node = (Node*)malloc(sizeof(Node));

    node->data = data;
    node->left = NULL;
    node->right =NULL;
    node->v = 0;

    return node;
}

Node* insertNode(Node* root ,int key){
    if(root == NULL)    return createNode(key);

    if(key<=root->data){
        root->left = insertNode(root->left , key);
        root->v++;
    }
    else{
        root->right = insertNode(root->right ,key);
        root->v++;
    }
    return root;
}
Node* inorderSucc(Node* root){
    if(root ==NULL) return NULL;

    Node* temp = root;
    while(temp->left)   temp = temp->left;

    return temp;
}
Node* deleteNode(Node* root,int key){
    if(root ==NULL) return NULL;

    if(key<root->data){
        root->left = deleteNode(root->left,key);
        root->v --;
    }
    else if(key>root->data){
        root->right = deleteNode(root->right,key);
        root->v--;
    }
    else{
        if(root->left == NULL){
            Node* temp = root->right ;
            free(root);
            return temp;
        }
        else if(root->right ==NULL){
            Node* temp = root->left;
            free(root);
            return temp;
        }
        else{
            Node* x = inorderSucc(root->right);
            root->data = x->data;
            root->right = deleteNode(root->right,x->data);
        }
    }
    return root;
}


int main(){
    Node* root = NULL;
    int arr[] = {12,5,8,19,10,15,6,4,14};
    int n = sizeof(arr)/sizeof(arr[0]);

    for(int i=0;i<n;i++){
        root = insertNode(root,arr[i]);
    }
    // printf("%d ",root->v);
    // printf("%d ",root->left->v);

    root = deleteNode(root,10);

    printf("%d ",root->v);
    printf("%d ",root->left->v);
    printf("%d ",root->left->right->v);



}