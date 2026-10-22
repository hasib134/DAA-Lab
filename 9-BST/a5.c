#include<stdio.h>
#include<stdlib.h>

//Revision 

typedef struct Node{
    int data;
    void* satelliteData;
    struct Node* parent;
    struct Node* left;
    struct Node* right;
}Node;

Node* createNode(int data){
    Node* node = (Node*)malloc(sizeof(Node));
    node->left = NULL;
    node->parent = NULL;
    node->right = NULL;
    node->data = data;
    node->satelliteData = NULL;
    return node;
}

Node* insert(Node* root ,int key){
    if(root == NULL)    return createNode(key);

    Node* curr = root;
    Node* y = NULL;
    while(curr!=NULL){
        y = curr;
        if(key<curr->data){
            curr = curr->left;
        }
        else{
            curr = curr->right;
        }
    }

    Node* newNode = createNode(key);
    newNode->parent = y;

    if(key<y->data){
        y->left = newNode;
    }
    else{
        y->right = newNode;
    }
    return root;
}

void inorder(Node* root){
    if(root == NULL)    return;

    inorder(root->left);
    printf("%d ",root->data);
    inorder(root->right);
}

Node* buildBST(int arr[] , int n){
    Node* root = NULL;
    for(int i=0;i<n;i++){
        root = insert(root,arr[i]);
    }
    return root;
}

Node* successor(Node* node){
    Node* curr = node;
    while(curr->left){
        curr = curr->left;
    }
    return curr;
}

Node* search(Node* root,int key){
    Node* curr = root;
    while(curr!=NULL){
        if(curr->data == key){
            return curr;
        }
        else if(key<curr->data){
            curr = curr->left;
        }
        else{
            curr = curr->right;
        }
    }
    return NULL;
}

Node* transplant(Node* root,Node* u,Node* v){
    if(u->parent == NULL){
        root = v;
    }
    else if(u == u->parent->left){
        u->parent->left = v;
    }
    else{
        u->parent->right = v;
    }

    if(v!=NULL){
        v->parent= u->parent;
    }
    return root;
}

Node* deleteBST(Node* root,int key){
    Node* z = search(root,key);
    if(z ==NULL)    return root;

    if(z->left ==NULL){
        //left child is null
        root = transplant(root,z,z->right);
    }
    else if(z->right == NULL){
        //right child is null
        root = transplant(root,z,z->left);
    }
    else{
        // both child are present;
        Node* y = successor(z->right);
        if(y!=z->right){
            root = transplant(root,y,y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        root = transplant(root,z,y);
        y->left = z->left;
        y->left->parent = y;
    }
    free(z);
    return root;

}

int main(){
    int arr[]= {4,6,8,1,3,5,8,10,32,12};
    int n = sizeof(arr)/sizeof(arr[0]);

    Node* root = buildBST(arr,n);

    inorder(root);
    printf("\n");

    root = deleteBST(root,10);
    inorder(root);
    printf("\n");
    
}