#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
}Node;

Node* createNode(int data){
    Node* node =(Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = NULL;
    node->parent  = NULL;
    node->right = NULL;
    return node;
}

Node* insert(Node* root ,int key){
    if(root == NULL)    return createNode(key);

    Node* curr = root;
    Node* parent = NULL;

    while(curr!=NULL){
        parent = curr;
        if(key <= curr->data){
            curr = curr->left;
        }
        else{
            curr = curr->right;
        }
    }
    Node* newNode= createNode(key);
    newNode->parent = parent;
    if(key<=parent->data){
        parent->left = newNode;
    }
    else{
        parent->right = newNode;
    }
    return root;
}

void inorder(Node* root){
    if(root == NULL)    return;

    inorder(root->left);
    printf("%d ",root->data);
    inorder(root->right);
}

 
Node* successor(Node* node){
    if(node == NULL)    return NULL;

    Node* curr = node;
    while(curr->left){
        curr = curr->left;
    }
    return curr;
}   

Node* search(Node* root,int key){
    if(root == NULL)    return NULL;
    Node* curr = root;
    while(curr!=NULL){
        if(curr->data == key){
            return curr;
        }
        else if(key < curr->data){
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

    if(v!=NULL) v->parent = u->parent;

    return root;
}  

Node* delete(Node* root , int key){
    Node* z = search(root,key);
    if(z==NULL) return root;

    if(z->left ==NULL){
        root = transplant(root,z,z->right);
    }
    else if (z->right ==NULL){
        root = transplant(root,z,z->left);
    }
    else{
        //find the successor of z
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
    Node* root = NULL;
    int arr[] = {4,6,3,4,6,8,1,0,9,7};
    int n= sizeof(arr)/sizeof(arr[0]);
    for(int i=0;i<n;i++){
        root = insert(root,arr[i]);
    }

    inorder(root);
    printf("\n");

    root =  delete(root,9);
    inorder(root);
    printf("\n");
}
