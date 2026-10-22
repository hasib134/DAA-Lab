#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    void * satelliteData;
    struct Node* right;
    struct Node* left;
    struct Node* parent;
}Node;

Node* createNode(int data){
    Node* node = (Node*)malloc(sizeof(Node));
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    node->satelliteData = NULL;
    node->data = data;
    return node;
}

Node* insert(Node* root,int key){
    if(root == NULL)    return createNode(key);

    Node* curr = root;
    Node* y = NULL;

    while(curr!=NULL){
        y = curr;
        if(key < curr->data){
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

Node* search(Node* root , int key){
    Node* curr = root;
    while(curr!=NULL){
        if(key == curr->data){
            return curr;
        }
        else if(key<curr->data){
            curr == curr->left;
        }
        else{
            curr = curr->right;
        }
    }
    return NULL;
}

Node* transplant(Node* root , Node* u,Node* v){
    if(u->parent == NULL){
        root = v;
    }
    else if(u == u->parent->left){
        u->parent->left= v;
    }
    else {
        u->parent->right = v;
    }

    if(v!=NULL){
        v->parent = u->parent;
    }
    return root;
}

Node* successor(Node* node){
    Node* curr = node;
    while(curr->left!=NULL){
        curr = curr->right;
    }
    return curr;
}

Node* deleteBST(Node* root,int key){
    Node* z =search(root,key);

    if(z->left == NULL){
        root = transplant(root,z,z->right);
    }
    else if(z->right == NULL){
        root = transplant(root,z,z->left);
    }
    else{

        Node* y  =successor(z->right);
        if(y!=z->right){
            transplant(root,y,y->right);
            y->left= z->left;
            y->left->parent = y;
        }
        transplant(root,z,y);
        y->right = z->right;
        y->right->parent = y;
    }
    free(z);
    return
}


int main(){

}